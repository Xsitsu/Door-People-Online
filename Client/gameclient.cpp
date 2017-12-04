#include "gameclient.hpp"

#include "util/logger.hpp"

GameClient::GameClient() : Client(), display(nullptr), event_queue(nullptr), timer(nullptr), datamodel()
{
    this->display = al_create_display(1152, 648);
    this->event_queue = al_create_event_queue();
    this->timer = al_create_timer(1.0 / 60);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_set_window_position(display, 10, 10);
}

GameClient::~GameClient()
{
    al_destroy_display(this->display);
    al_destroy_event_queue(this->event_queue);
    al_destroy_timer(this->timer);

    this->display = nullptr;
    this->event_queue = nullptr;
    this->timer = nullptr;
}

void GameClient::Run()
{
    bool needsDraw = false;
    bool running = true;
    al_start_timer(this->timer);
    while (running)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(this->event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            needsDraw = true;

            this->Tick();

            Util::Logger::Instance()->Flush();
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

    if(this->IsConnected())
    {
        this->Disconnect();
    }
}
