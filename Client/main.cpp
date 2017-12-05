#include <sstream>

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_native_dialog.h"

#include "Util/logger.hpp"
#include "gameclient.hpp"

int main()
{
    unsigned int connectPort = 50000;
    Network::Address serverAddress(127, 0, 0, 1, 50000);

    Util::Logger::Instance()->CreateLogChannel("main", "MAIN", stdout);
    Util::Logger::Instance()->EnableLogChannel("main");

    if (!al_init())
    {
        Util::Logger::Instance()->Log("main", "Failed to initialize allegro!\n");
        Util::Logger::Instance()->Flush();
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
        Util::Logger::Instance()->Log("main", stream.str());
        //Util::Logger::Instance()->Flush();
    }

    std::stringstream stream;
    stream << "Created client on port: " << connectPort << "\n";
    Util::Logger::Instance()->Log("main", stream.str());
    Util::Logger::Instance()->Flush();

    try
    {
        client.Connect(serverAddress);
        client.Run();
    }
    catch (...)
    {
        Util::Logger::Instance()->Log("main", "An error happened. Not sure what.\n");
        if (client.IsConnected())
        {
            client.Disconnect();
        }
    }

    Util::Logger::Instance()->Flush();

    Network::ShutdownSockets();

    return 0;
}
