#include <sstream>

#include "util/log/logger.hpp"

#include "gameserver.hpp"

int main(int argc, char *argv[])
{
    Network::InitializeSockets();

    Util::Log* log = Util::Logger::Instance()->GetLog("Main");
    FILE* log_file = stdout;

    unsigned int bindPort = 50000;
    GameServer server;
    if (!server.Init(bindPort, 20))
    {
        std::stringstream stream;
        stream << "Unable to bind to port: " << bindPort << "!\n";
        log->LogMessage(stream.str(), Util::LogLevel::Fatal);
        Util::Logger::Instance()->WriteAll(log_file);
        return -1;
    }

    std::stringstream stream;
    stream << "Successfully bound to port: " << bindPort << "!\n";
    log->LogMessage(stream.str(), Util::LogLevel::Info);
    log->Write(log_file);

    try
    {
        server.Run();
    }
    catch (...)
    {

    }

    Util::Logger::Instance()->WriteAll(log_file);

    Network::ShutdownSockets();

    return 0;
}

