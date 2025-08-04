#include <sstream>

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_native_dialog.h"

#include "util/log/logger.hpp"
#include "game.hpp"

int main()
{
    Util::Log* log = Util::Logger::Instance()->GetLog("Main");

    if (!al_init())
    {
        std::string msg = "Failed to initialize allegro!\n";
        log->LogMessage(msg, Util::LogLevel::Fatal);
        Util::Logger::Instance()->WriteAll();
        return -1;
    }

    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();

    GameStandalone game;
    try
    {
        game.Run();
    }
    catch (...)
    {
        std::string msg = "An error happened. Not sure what.\n";
        log->LogMessage(msg, Util::LogLevel::Fatal);
    }

    Util::Logger::Instance()->WriteAll();

    return 0;
}