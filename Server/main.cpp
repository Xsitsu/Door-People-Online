#include <sstream>

#include "Util/logger.hpp"

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

    try
    {
        server.Run();
    }
    catch (...)
    {

    }

    Util::Logger::Instance()->Flush();

    Network::ShutdownSockets();

    return 0;
}

