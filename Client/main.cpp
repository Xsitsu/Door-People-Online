#include <sstream>

#include "util/logger.hpp"

#include "network/client.hpp"

int main()
{
    Network::Address serverAddress(127, 0, 0, 1, 50000);

    Network::InitializeSockets();

    Util::Logger::Instance()->CreateLogChannel("main", "MAIN", stdout);
    Util::Logger::Instance()->EnableLogChannel("main");

    unsigned int connectPort = 50000;
    Network::Client client;
    while (!client.Init(connectPort))
    {
        connectPort++;
        std::stringstream stream;
        stream << "Trying on port: ";
        stream << connectPort;
        stream << "\n";
        Util::Logger::Instance()->Log("main", stream.str());
        Util::Logger::Instance()->Flush();
    }

    std::stringstream stream;
    stream << "Created client on port: ";
    stream << connectPort;
    stream << "\n";
    Util::Logger::Instance()->Log("main", stream.str());
    Util::Logger::Instance()->Flush();

    client.Connect(serverAddress);

    while (true)
    {

    }

    Util::Logger::Instance()->Flush();

    Network::ShutdownSockets();

    return 0;
}
