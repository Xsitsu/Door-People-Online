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
    this->isRunning = true;

    Game::World *world = reinterpret_cast<Game::World*>(this->dataModel.GetService("World"));

    Util::Timer timer;
    timer.Start();
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
