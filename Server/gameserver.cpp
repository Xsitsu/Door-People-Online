#include "gameserver.hpp"

#include "util/logger.hpp"

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
    playerList->AddPlayer(player);

    Network::Packet::Player npPacket = Network::Packet::Player(0, Network::PacketAction::ACTION_ADD);
    npPacket.SetPlayerId(player->GetNetworkOwner());
    npPacket.SetDir(player->GetDirection());
    npPacket.SetPosX(player->GetPosition().x);
    npPacket.SetPosY(player->GetPosition().y);
    npPacket.SetVelX(player->GetVelocity().x);
    npPacket.SetVelY(player->GetVelocity().y);

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
        npPacket.SetPlayerId(player->GetNetworkOwner());

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

}

