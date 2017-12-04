#include "gameserver.hpp"

#include "util/logger.hpp"

#include "gamecore/world.hpp"

GameServer::GameServer() : Server(), dataModel(), isRunning(false)
{
    this->dataModel.Init();
}

GameServer::~GameServer()
{

}

void GameServer::Run()
{
    Game::World *world = this->GetWorld();
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
            world->Update(deltaT);

            Util::Logger::Instance()->Flush();
        }
    }
}

Game::World* GameServer::GetWorld()
{
    return reinterpret_cast<Game::World*>(this->dataModel.GetService("World"));
}

bool GameServer::HandlePacket(Network::Packet::Terrain *packet, const Network::Address &sender)
{
    if (packet->GetAction() == Network::PacketAction::ACTION_REQUEST)
    {
        Game::World *world = this->GetWorld();

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
