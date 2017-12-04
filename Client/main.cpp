#include <sstream>

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_native_dialog.h"

#include "util/logger.hpp"

#include "network/client.hpp"

int main()
{
    unsigned int connectPort = 50000;
    Network::Client client;
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

    ALLEGRO_DISPLAY *display = al_create_display(1280, 720);
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_set_window_position(display, 10, 10);

    Network::InitializeSockets();

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

    client.Connect(serverAddress);

    bool needsDraw = false;
    bool running = true;
    al_start_timer(timer);
    while (running)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            needsDraw = true;
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            running = false;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {

        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {

        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
        {

        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {

        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {

        }

        if (needsDraw && al_is_event_queue_empty(event_queue))
        {
            needsDraw = false;

            al_wait_for_vsync();
            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));

        }

    }

    Util::Logger::Instance()->Flush();

    Network::ShutdownSockets();

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);

    return 0;
}
