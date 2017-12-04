#include <sstream>

#include "util/logger.hpp"
#include "util/timer.hpp"

#include "gamecore/datamodel.hpp"
#include "gamecore/world.hpp"

#include "gameserver.hpp"

int main(int argc, char *argv[])
{
    Network::InitializeSockets();

    Util::Logger::Instance()->CreateLogChannel("main", "MAIN", stdout);
    Util::Logger::Instance()->EnableLogChannel("main");

    unsigned int bindPort = 50000;
    GameServer server;
    if (!server.Init(bindPort, 20))
    {
        std::stringstream stream;
        stream << "Unable to bind to port: " << bindPort << "!\n";
        Util::Logger::Instance()->Log("main", stream.str());
        Util::Logger::Instance()->Flush();
        return -1;
    }

    std::stringstream stream;
    stream << "Successfully bound to port: " << bindPort << "!\n";
    Util::Logger::Instance()->Log("main", stream.str());
    Util::Logger::Instance()->Flush();

    Game::DataModel dataModel;
    dataModel.Init();
    Game::World *world = reinterpret_cast<Game::World*>(dataModel.GetService("World"));

    Util::Timer timer;
    timer.Start();
    while (server.IsRunning())
    {
        double deltaT = timer.GetMiliSeconds();
        if (deltaT >= 16)
        {
            //Util::Logger::Instance()->Log("main", "Tick\n");
            timer.Reset();
            server.Tick();
            world->Update(deltaT);
        }

        Util::Logger::Instance()->Flush();
    }

    Util::Logger::Instance()->Flush();

    Network::ShutdownSockets();

    return 0;
}

