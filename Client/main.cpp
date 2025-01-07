#include <sstream>

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_native_dialog.h"

#include "Util/log/logger.hpp"
#include "gameclient.hpp"

int main()
{
    unsigned int connectPort = 50000;
    Network::Address serverAddress(127, 0, 0, 1, 50000);

    Util::Log* log = Util::Logger::Instance()->GetLog("Main");

    if (!al_init())
    {
        std::string msg = "Failed to initialize allegro!\n";
        log->LogMessage(msg, Util::LogLevel::Fatal);
        Util::Logger::Instance()->WriteAll(stderr);
        return -1;
    }

    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    Network::InitializeSockets();

    GameClient client;
    while (!client.Init(connectPort))
    {
        connectPort++;
        std::stringstream stream;
        stream << "Trying on port: " << connectPort << "\n";
        log->LogMessage(stream.str(), Util::LogLevel::Info);
    }

    std::stringstream stream;
    stream << "Created client on port: " << connectPort << "\n";
    log->LogMessage(stream.str(), Util::LogLevel::Info);
    log->Write(stdout);

    try
    {
        client.Connect(serverAddress);
        client.Run();
    }
    catch (...)
    {
        std::string msg = "n error happened. Not sure what.\n";
        log->LogMessage(msg, Util::LogLevel::Fatal);
        log->Write(stderr);

        if (client.IsConnected())
        {
            client.Disconnect();
        }
    }

    Util::Logger::Instance()->WriteAll(stdout);

    Network::ShutdownSockets();

    return 0;
}
