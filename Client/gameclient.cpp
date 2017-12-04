#include "gameclient.hpp"

#include "util/logger.hpp"
#include "util/timer.hpp"

#include "gamecore/world.hpp"
#include "gamecore/terrain.hpp"
#include "gamecore/platform.hpp"
#include "gamecore/wall.hpp"

#include "actordrawer.hpp"
#include "terraindrawer.hpp"

GameClient::GameClient() : Client(), display(nullptr), event_queue(nullptr), timer(nullptr), dataModel(), isRunning(false), player(nullptr)
{
    dataModel.Init();

    this->display = al_create_display(1152, 648);
    this->event_queue = al_create_event_queue();
    this->timer = al_create_timer(1.0 / 60);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_set_window_position(display, 10, 10);
}

GameClient::~GameClient()
{
    al_destroy_display(this->display);
    al_destroy_event_queue(this->event_queue);
    al_destroy_timer(this->timer);

    this->display = nullptr;
    this->event_queue = nullptr;
    this->timer = nullptr;
}

void GameClient::Run()
{
    Game::Vector2 drawBegin(1152 / 2, 648 * 0.8);

    Game::World *world = this->dataModel.GetWorld();

    Game::Vector2 walkSpeed(160, 0);

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

            Util::Logger::Instance()->Flush();
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            this->isRunning = false;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (this->player)
            {
                if (ev.keyboard.keycode == ALLEGRO_KEY_UP)
                {
                    if (this->player->GetVelocity().y == 0)
                    {
                        this->player->Jump();
                    }
                }
                else if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT)
                {
                    this->player->AddVelocity(-walkSpeed);
                    if (this->player->GetDirection() != Game::Actor::Direction::DIR_LEFT)
                    {
                        this->player->SetDirection(Game::Actor::Direction::DIR_LEFT);
                    }
                }
                else if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                {
                    this->player->AddVelocity(walkSpeed);
                    if (this->player->GetDirection() != Game::Actor::Direction::DIR_RIGHT)
                    {
                        this->player->SetDirection(Game::Actor::Direction::DIR_RIGHT);
                    }
                }
                else if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN)
                {

                }
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            if (this->player)
            {
                if (ev.keyboard.keycode == ALLEGRO_KEY_UP)
                {

                }
                else if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT)
                {
                    this->player->AddVelocity(walkSpeed);
                }
                else if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                {
                    this->player->AddVelocity(-walkSpeed);
                }
                else if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN)
                {

                }
            }
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

            if (world->IsTerrainLoaded())
            {
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
                    TerrainDrawer::DrawTerrain(terrainObj, drawBegin, col);
                }

                std::list<Game::Actor*> actors = world->GetActors();
                for (Game::Actor *actor : actors)
                {
                    if (actor->IsPlayer())
                    {
                        Game::Player *player = static_cast<Game::Player*>(actor);
                        if (player != this->player)
                        {
                            ActorDrawer::DrawActor(player, drawBegin, al_map_rgb(0, 255, 255));
                        }
                    }
                }

                if (this->player)
                {
                    ActorDrawer::DrawActor(this->player, drawBegin, al_map_rgb(255, 255, 0));
                }
            }


            al_wait_for_vsync();
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
    bool wasHandled = Network::Client::HandlePacket(packet, sender);
    if (wasHandled)
    {
        if (this->isConnected)
        {
            Network::Packet::Terrain packet(this->connectionId, Network::PacketAction::ACTION_REQUEST);
            this->SendPacket(&packet, this->serverAddress);

            Game::PlayerList *playerList = this->dataModel.GetPlayerList();
            Game::Player *player = new Game::Player();
            player->SetNetworkOwner(this->connectionId);
            playerList->AddPlayer(player);

            this->player = player;
        }
        else
        {
            this->isRunning = false;
        }

    }
    return wasHandled;
}

bool GameClient::HandlePacket(Network::Packet::Terrain *packet, const Network::Address &sender)
{
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

        return true;
    }

    return false;
}
