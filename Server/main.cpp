#include "util/serviceprovider.hpp"
#include "util/logger.hpp"


int main(int argc, char *argv[])
{
    Util::ServiceProvider provider;
    Util::Logger *logger = static_cast<Util::Logger*>(provider.GetService("Logger"));

    logger->CreateLogChannel("test", "TST", stdout);
    logger->EnableLogChannel("test");
    logger->Log("test", "test logging\n");
    logger->FlushAll();

    return 0;
}
