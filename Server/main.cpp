#include "util/serviceprovider.hpp"
#include "util/logger.hpp"

#include "network/socket.hpp"

int main(int argc, char *argv[])
{
    Network::InitializeSockets();

    Util::ServiceProvider provider;

    Util::Logger::Instance()->CreateLogChannel("test", "TST", stdout);
    Util::Logger::Instance()->EnableLogChannel("test");
    Util::Logger::Instance()->Log("test", "test logging\n");
    Util::Logger::Instance()->Flush();

    Network::ShutdownSockets();

    return 0;
}
