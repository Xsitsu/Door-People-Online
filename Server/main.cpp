#include <sstream>

#include "util/logger.hpp"

#include "network/server.hpp"

int main(int argc, char *argv[])
{
    Network::InitializeSockets();

    Util::Logger::Instance()->CreateLogChannel("main", "MAIN", stdout);
    Util::Logger::Instance()->EnableLogChannel("main");

    unsigned int bindPort = 50000;
    Network::Server server;
    if (!server.Init(bindPort, 20))
    {
        std::stringstream stream;
        stream << "Unable to bind to port: ";
        stream << bindPort;
        stream << "!\n";
        Util::Logger::Instance()->Log("main", stream.str());
        Util::Logger::Instance()->Flush();
        return -1;
    }

    std::stringstream stream;
    stream << "Successfully bound to port: ";
    stream << bindPort;
    stream << "!\n";
    Util::Logger::Instance()->Log("main", stream.str());
    Util::Logger::Instance()->Flush();

    while (server.IsRunning())
    {
        server.Tick();
        Util::Logger::Instance()->Flush();
    }

    Util::Logger::Instance()->Flush();

    Network::ShutdownSockets();

    return 0;
}

