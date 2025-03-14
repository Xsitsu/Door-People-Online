#include "gameclient.hpp"

#include "util/timer.hpp"

#include "gamecore/world.hpp"
#include "gamecore/terrain.hpp"
#include "gamecore/platform.hpp"
#include "gamecore/wall.hpp"

#include "actordrawer.hpp"
#include "terraindrawer.hpp"

GameClient::GameClient() : Client(), display(nullptr), event_queue(nullptr), timer(nullptr), dataModel(), isRunning(false), player(nullptr)
{
    this->log = Util::Logger::Instance()->GetLog("GameClient");
    this->log->SetLogLevel(Util::LogLevel::Info);

    dataModel.Init();

    this->display = al_create_display(1152, 648);
    this->event_queue = al_create_event_queue();
    this->timer = al_create_timer(1.0 / 60);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_set_window_position(display, 40, 40);
}

GameClient::~GameClient()
{
    al_destroy_display(this->display);
    al_destroy_event_queue(this->event_queue);
    al_destroy_timer(this->timer);

    this->display = nullptr;
    this->event_queue = nullptr;
    this->timer = nullptr;

    this->log = nullptr;
}

void GameClient::Run()
{
    Game::Vector2 drawBegin(1152 / 2, 648 * 0.8);

    Game::World *world = this->dataModel.GetWorld();

    Util::Timer uTimer;

    bool needsDraw = false;
    this->isRunning = true;
    al_start_timer(this->timer);
    uTimer.Start();
    while (this->isRunning)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(this->event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            needsDraw = true;

            this->Tick();
            Game::World *world = this->dataModel.GetWorld();

            double deltaT = uTimer.GetMiliSeconds();
            uTimer.Reset();
            world->Update(deltaT/1000);

            if (this->player != nullptr && this->player_controller->NeedsPhysicsUpdate())
            {
                this->player_controller->ClearPhysicsUpdate();
                this->SendPhysicsUpdateToServer();
            }

            Util::Logger::Instance()->WriteAll();
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            this->isRunning = false;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            this->HandleKeyDown(ev.keyboard.keycode);
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            this->HandleKeyUp(ev.keyboard.keycode);
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
        {

        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {

        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {

        }

        if (needsDraw && al_is_event_queue_empty(event_queue))
        {
            needsDraw = false;

            if (world->IsTerrainLoaded() && this->player)
            {
                Game::Vector2 drawFocus = drawBegin - Game::Vector2(player->GetPosition().x, 0);

                std::list<Game::Terrain*> terrain = world->GetTerrain();
                for (Game::Terrain *terrainObj : terrain)
                {
                    ALLEGRO_COLOR col = al_map_rgb(255, 255, 255);
                    if (terrainObj->GetTerrainType() == Game::TerrainType::TYPE_PLATFORM)
                    {
                        col = al_map_rgb(20, 20, 220);
                    }
                    else if (terrainObj->GetTerrainType() == Game::TerrainType::TYPE_WALL)
                    {
                        col = al_map_rgb(20, 220, 20);
                    }
                    TerrainDrawer::DrawTerrain(terrainObj, drawFocus, col);
                }

                std::list<Game::Actor*> actors = world->GetActors();
                for (Game::Actor *actor : actors)
                {
                    if (actor->IsPlayer())
                    {
                        Game::Player *player = static_cast<Game::Player*>(actor);
                        if (player != this->player)
                        {
                            ActorDrawer::DrawActor(player, drawFocus, al_map_rgb(0, 255, 255));
                        }
                    }
                }

                ActorDrawer::DrawActor(this->player, drawFocus, al_map_rgb(255, 255, 0));
            }


            //al_wait_for_vsync();
            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));
        }

    }

    if(this->IsConnected())
    {
        this->Disconnect();
    }
}

bool GameClient::HandlePacket(Network::Packet::Connect *packet, const Network::Address &sender)
{
    this->log->LogMessage("GameClient::HandlePacket(Packet::Connect)\n", Util::LogLevel::Debug);

    bool wasHandled = Network::Client::HandlePacket(packet, sender);
    if (wasHandled)
    {
        if (this->isConnected)
        {
            this->RequestTerrainFromServer();
            this->RequestPhysicsSettingsFromServer();
            this->CreatePlayerForClient();
        }
        else
        {
            this->isRunning = false;
        }
    }
    return wasHandled;
}


bool GameClient::HandlePacket(Network::Packet::Disconnect *packet, const Network::Address &sender)
{
    this->log->LogMessage("GameClient::HandlePacket(Packet::Disconnect)\n", Util::LogLevel::Debug);

    if (packet->GetAction() == Network::PacketAction::ACTION_TELL)
    {
        this->isRunning = false;
    }

    return true;
}

bool GameClient::HandlePacket(Network::Packet::Terrain *packet, const Network::Address &sender)
{
    this->log->LogMessage("GameClient::HandlePacket(Packet::Terrain)\n", Util::LogLevel::Debug);

    if (packet->GetAction() == Network::PacketAction::ACTION_TELL)
    {
        Game::World* world = this->dataModel.GetWorld();
        world->ClearTerrain();

        std::list<Network::Packet::Terrain::TerrainData> terrainData = packet->GetTerrainData();
        for (Network::Packet::Terrain::TerrainData tData : terrainData)
        {
            Game::TerrainType tType = static_cast<Game::TerrainType>(tData.type);
            Game::Vector2 position((int)tData.posX, (int)tData.posY);
            Game::Vector2 size((int)tData.sizeX, (int)tData.sizeY);

            Game::Terrain *terrain = nullptr;
            if (tType == Game::TerrainType::TYPE_PLATFORM)
            {
                terrain = new Game::Platform();
            }
            else if (tType == Game::TerrainType::TYPE_WALL)
            {
                terrain = new Game::Wall();
            }

            if (terrain)
            {
                terrain->SetPosition(position);
                terrain->SetSize(size);
                world->AddTerrain(terrain);
            }
        }

        world->SetTerrainIsLoaded(true);
        this->log->LogMessage("Loaded terrain downloaded from server\n", Util::LogLevel::Info);

        return true;
    }

    return false;
}


bool GameClient::HandlePacket(Network::Packet::Player *packet, const Network::Address &sender)
{
    this->log->LogMessage("GameClient::HandlePacket(Packet::Player)\n", Util::LogLevel::Debug);

    Game::PlayerList *playerList = this->dataModel.GetPlayerList();
    if (packet->GetAction() == Network::PacketAction::ACTION_ADD)
    {
        std::list<Network::Packet::Player::PlayerData> playerData = packet->GetPlayerData();
        for (Network::Packet::Player::PlayerData pData : playerData)
        {
            if (!playerList->GetPlayerWithNetworkId(pData.playerId))
            {
                Game::Player *player = new Game::Player();
                player->SetNetworkOwner(pData.playerId);

                Game::Actor::Direction direction = static_cast<Game::Actor::Direction>(pData.direction);
                Game::Vector2 position((int)pData.posX, (int)pData.posY);
                Game::Vector2 velocity((int)pData.velX, (int)pData.velY);

                player->SetDirection(direction);
                player->SetPosition(position);
                player->SetVelocity(velocity);

                playerList->AddPlayer(player);
            }
        }

        return true;
    }
    else if (packet->GetAction() == Network::PacketAction::ACTION_REMOVE)
    {
        std::list<Network::Packet::Player::PlayerData> playerData = packet->GetPlayerData();
        for (Network::Packet::Player::PlayerData pData : playerData)
        {
            Game::Player *player = playerList->GetPlayerWithNetworkId(pData.playerId);
            if (player)
            {
                playerList->RemovePlayer(player);
                delete player;
            }
        }
        return true;
    }
    else if (packet->GetAction() == Network::PacketAction::ACTION_TELL)
    {
        std::list<Network::Packet::Player::PlayerData> playerData = packet->GetPlayerData();
        for (Network::Packet::Player::PlayerData pData : playerData)
        {
            Game::Player *player = playerList->GetPlayerWithNetworkId(pData.playerId);
            if (player)
            {
                Game::Actor::Direction direction = static_cast<Game::Actor::Direction>(pData.direction);
                Game::Vector2 position((int)pData.posX, (int)pData.posY);
                Game::Vector2 velocity((int)pData.velX, (int)pData.velY);

                player->SetDirection(direction);
                player->SetPosition(position);
                player->SetVelocity(velocity);
            }
        }
        return true;
    }
    return false;
}

bool GameClient::HandlePacket(Network::Packet::PhysicsSettings *packet, const Network::Address &sender)
{
    this->log->LogMessage("GameClient::HandlePacket(Packet::PhysicsSettings)\n", Util::LogLevel::Debug);

    if (packet->GetAction() == Network::PacketAction::ACTION_TELL)
    {
        this->dataModel.GetWorld()->SetPhysicsSettings(packet->GetPhysicsSettings());

        std::string phys_str = this->dataModel.GetWorld()->GetPhysicsSettings().ToStr();
        this->log->LogMessage("Updated physics settings downloaded from server: " + phys_str + "\n", Util::LogLevel::Info);

        return true;
    }
    return false;
}


void GameClient::HandleKeyDown(int keycode)
{
    bool is_controlling_character = (this->player != nullptr);
    if (is_controlling_character)
    {
        if (keycode == ALLEGRO_KEY_UP)
        {
            this->player_controller->Jump();
        }
        else if (keycode == ALLEGRO_KEY_LEFT)
        {
            this->player_controller->Move(Game::Actor::Direction::Left);
        }
        else if (keycode == ALLEGRO_KEY_RIGHT)
        {
            this->player_controller->Move(Game::Actor::Direction::Right);
        }
    }
}

void GameClient::HandleKeyUp(int keycode)
{
    bool is_controlling_character = (this->player != nullptr);
    if (is_controlling_character)
    {
        ALLEGRO_KEYBOARD_STATE keyboardState;
        al_get_keyboard_state(&keyboardState);
        if (keycode == ALLEGRO_KEY_LEFT)
        {
            this->player_controller->StopMoving(Game::Actor::Direction::Left);
            if (al_key_down(&keyboardState, ALLEGRO_KEY_RIGHT))
            {
                this->player_controller->Move(Game::Actor::Direction::Right);
            }
        }
        else if (keycode == ALLEGRO_KEY_RIGHT)
        {
            this->player_controller->StopMoving(Game::Actor::Direction::Right);
            if (al_key_down(&keyboardState, ALLEGRO_KEY_LEFT))
            {
                this->player_controller->Move(Game::Actor::Direction::Left);
            }
        }
    }
}


void GameClient::RequestTerrainFromServer()
{
    Network::Packet::Terrain packet(this->connectionId, Network::PacketAction::ACTION_REQUEST);
    this->SendPacket(&packet, this->serverAddress);
    this->log->LogMessage("Sent terrain download request to server\n", Util::LogLevel::Info);
}

void GameClient::RequestPhysicsSettingsFromServer()
{
    Network::Packet::PhysicsSettings packet(this->connectionId, Network::PacketAction::ACTION_REQUEST);
    this->SendPacket(&packet, this->serverAddress);
    this->log->LogMessage("Sent physics settings request to server\n", Util::LogLevel::Info);
}

void GameClient::CreatePlayerForClient()
{
    Game::PlayerList *playerList = this->dataModel.GetPlayerList();
    Game::Player *player = new Game::Player();
    player->SetNetworkOwner(this->connectionId);
    playerList->AddPlayer(player);

    this->player = player;
    this->player_controller = new PlayerController(this->player);

    this->log->LogMessage("Created new player for this client\n", Util::LogLevel::Info);
}


void GameClient::SendPhysicsUpdateToServer()
{
    this->log->LogMessage("GameClient::SendPhysicsUpdateToServer()\n", Util::LogLevel::Debug);

    Network::Packet::Player packet(this->connectionId, Network::PacketAction::ACTION_TELL);

    Network::Packet::Player::PlayerData npData;
    npData.playerId = this->player->GetNetworkOwner();
    npData.direction = static_cast<uint8_t>(this->player->GetDirection());
    npData.posX = (int)this->player->GetPosition().x;
    npData.posY = (int)this->player->GetPosition().y;
    npData.velX = (int)this->player->GetVelocity().x;
    npData.velY = (int)this->player->GetVelocity().y;
    packet.AddPlayerData(npData);

    this->SendPacket(&packet, this->serverAddress);
}