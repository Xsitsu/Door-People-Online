#include "gameserver.hpp"

#include "Util/logger.hpp"

GameServer::GameServer() : Server(), dataModel(), isRunning(false)
{
    this->dataModel.Init();
}

GameServer::~GameServer()
{

}

void GameServer::Run()
{
    Game::World *world = this->dataModel.GetWorld();
    world->LoadWorld();

    Util::Timer timer;
    timer.Start();
    this->isRunning = true;
    while (this->isRunning)
    {
        double deltaT = timer.GetMiliSeconds();
        if (deltaT >= 16)
        {
            //Util::Logger::Instance()->Log("main", "Tick\n");
            timer.Reset();
            this->Tick();
            world->Update(deltaT/1000);

            Util::Logger::Instance()->Flush();
        }
    }
}

void GameServer::ClientConnectionAdded(Network::ClientConnection *connection)
{
    Game::PlayerList *playerList = this->dataModel.GetPlayerList();
    Game::Player *player = new Game::Player();
    player->SetNetworkOwner(connection->GetConnectionId());

    Network::Packet::Player curPacket = Network::Packet::Player(0, Network::PacketAction::ACTION_ADD);
    for (Game::Player *other : playerList->GetPlayers())
    {
        Network::Packet::Player::PlayerData npData;
        npData.playerId = other->GetNetworkOwner();
        npData.direction = static_cast<uint8_t>(other->GetDirection());
        npData.posX = (int)other->GetPosition().x;
        npData.posY = (int)other->GetPosition().y;
        npData.velX = (int)other->GetVelocity().x;
        npData.velY = (int)other->GetVelocity().y;
        curPacket.AddPlayerData(npData);
    }

    playerList->AddPlayer(player);
    this->SendPacket(&curPacket, connection->GetAddress());

    Network::Packet::Player npPacket = Network::Packet::Player(0, Network::PacketAction::ACTION_ADD);
    Network::Packet::Player::PlayerData npData;
    npData.playerId = player->GetNetworkOwner();
    npData.direction = static_cast<uint8_t>(player->GetDirection());
    npData.posX = (int)player->GetPosition().x;
    npData.posY = (int)player->GetPosition().y;
    npData.velX = (int)player->GetVelocity().x;
    npData.velY = (int)player->GetVelocity().y;
    npPacket.AddPlayerData(npData);

    for (auto it : this->connections)
    {
        Network::ClientConnection *other = it.second;
        if (other != connection)
        {
            this->SendPacket(&npPacket, other->GetAddress());
        }
    }
}

void GameServer::ClientConnectionRemoving(Network::ClientConnection *connection)
{
    Game::PlayerList *playerList = this->dataModel.GetPlayerList();
    Game::Player *player = playerList->GetPlayerWithNetworkId(connection->GetConnectionId());
    if (player)
    {
        Network::Packet::Player npPacket = Network::Packet::Player(0, Network::PacketAction::ACTION_REMOVE);
        Network::Packet::Player::PlayerData npData;
        npData.playerId = player->GetNetworkOwner();
        npData.direction = static_cast<uint8_t>(player->GetDirection());
        npPacket.AddPlayerData(npData);

        for (auto it : this->connections)
        {
            Network::ClientConnection *other = it.second;
            if (other != connection)
            {
                this->SendPacket(&npPacket, other->GetAddress());
            }
        }


        playerList->RemovePlayer(player);
        delete player;
    }
}

bool GameServer::HandlePacket(Network::Packet::Terrain *packet, const Network::Address &sender)
{
    if (packet->GetAction() == Network::PacketAction::ACTION_REQUEST)
    {
        Game::World *world = this->dataModel.GetWorld();

        Network::Packet::Terrain packet(0, Network::PacketAction::ACTION_TELL);

        std::list<Game::Terrain*> terrain = world->GetTerrain();
        for (Game::Terrain* ter : terrain)
        {
            Game::Vector2 position = ter->GetPosition();
            Game::Vector2 size = ter->GetSize();

            Network::Packet::Terrain::TerrainData tData;
            tData.type = static_cast<uint8_t>(ter->GetTerrainType());
            tData.posX = (int)position.x;
            tData.posY = (int)position.y;
            tData.sizeX = (int)size.x;
            tData.sizeY = (int)size.y;

            packet.AddTerrainData(tData);
        }

        this->SendPacket(&packet, sender);
        return true;
    }
    return false;
}


bool GameServer::HandlePacket(Network::Packet::Player *packet, const Network::Address &sender)
{
    Game::PlayerList *playerList = this->dataModel.GetPlayerList();
    if (packet->GetAction() == Network::PacketAction::ACTION_TELL)
    {
        Network::ClientConnection *connection = this->GetConnectionFromAddress(sender);
        if (connection)
        {
            Network::Packet::Player sendOut(0, Network::PacketAction::ACTION_TELL);

            std::list<Network::Packet::Player::PlayerData> playerData = packet->GetPlayerData();
            for (Network::Packet::Player::PlayerData pData : playerData)
            {
                if (pData.playerId == connection->GetConnectionId())
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

                        sendOut.AddPlayerData(pData);
                    }
                }
            }

            for (auto it : this->connections)
            {
                Network::ClientConnection *other = it.second;
                if (other != connection)
                {
                    this->SendPacket(&sendOut, other->GetAddress());
                }
            }

            return true;
        }
        else
        {
            Network::Packet::Disconnect sendOut(0, Network::PacketAction::ACTION_TELL);
            this->SendPacket(&sendOut, sender);
        }
    }
    return false;
}

