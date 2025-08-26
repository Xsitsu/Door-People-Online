#include "game.hpp"

#include "util/timer.hpp"

#include "gamecore/world.hpp"

#include "graphics/drawer/actordrawer.hpp"
#include "graphics/drawer/terraindrawer.hpp"

GameStandalone::GameStandalone(): display(nullptr), event_queue(nullptr), timer(nullptr), dataModel(), isRunning(false), player(nullptr)
{
    this->log = Util::Logger::Instance()->GetLog("GameClient");
    this->log->SetLogLevel(Util::LogLevel::Info);

    this->dataModel.Init();
    this->dataModel.GetWorld()->GetTerrainHandler().LoadMockTerrain();
    this->dataModel.GetWorld()->GetPhysicsHandler().SetPhysicsSettings(
        Game::PhysicsSettings(560, 160, 280)
    );

    this->display = al_create_display(1152, 648);
    this->event_queue = al_create_event_queue();
    this->timer = al_create_timer(1.0 / 60);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_set_window_position(display, 40, 40);
}

GameStandalone::~GameStandalone()
{
    al_destroy_display(this->display);
    al_destroy_event_queue(this->event_queue);
    al_destroy_timer(this->timer);

    this->display = nullptr;
    this->event_queue = nullptr;
    this->timer = nullptr;

    this->log = nullptr;
}

void GameStandalone::Run()
{
    Game::Vector2 drawBegin(1152 / 2, 648 * 0.8);

    Game::World *world = this->dataModel.GetWorld();

    this->CreatePlayerForClient();

    Util::Timer uTimer;

    bool needsDraw = false;
    this->isRunning = true;
    al_start_timer(this->timer);
    uTimer.Start();
    while (this->isRunning)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(this->event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            needsDraw = true;

            Game::World *world = this->dataModel.GetWorld();

            double deltaT = uTimer.GetMiliSeconds();
            uTimer.Reset();
            world->Update(deltaT/1000);

            if (this->player != nullptr && this->player_controller->NeedsPhysicsUpdate())
            {
                this->player_controller->ClearPhysicsUpdate();
            }

            Util::Logger::Instance()->WriteAll();
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            this->isRunning = false;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            this->HandleKeyDown(ev.keyboard.keycode);
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            this->HandleKeyUp(ev.keyboard.keycode);
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

            Game::Vector2 drawFocus = drawBegin;

            if (this->player)
            {
                Game::Physics::PhysicsObject *obj = this->dataModel.GetWorld()->GetPhysicsHandler().GetPhysicsObject(this->player->GetPhysicsObjectHandle());

                Game::Vector2 drawFocus = drawBegin - Game::Vector2(obj->GetGameObject().position.x, 0);
            }

            this->DrawTerrain(drawFocus);



            if (this->player != nullptr)
            {
                this->DrawActors(drawFocus);
            }

            // bool canDrawActors = false;
            // if (canDrawActors)
            // {
            //     std::list<Game::Actor*> actors = world->GetActors();
            //     for (Game::Actor *actor : actors)
            //     {
            //         if (actor->IsPlayer())
            //         {
            //             Game::Player *player = static_cast<Game::Player*>(actor);
            //             if (player != this->player)
            //             {
            //                 ActorDrawer::DrawActor(this->world, player, drawFocus, al_map_rgb(0, 255, 255));
            //             }
            //         }
            //     }

            //     ActorDrawer::DrawActor(this->world, this->player, drawFocus, al_map_rgb(255, 255, 0));
            // }


            //al_wait_for_vsync();
            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));
        }

    }
}

void GameStandalone::DrawTerrain(const Game::Vector2 &drawBegin)
{
    const Game::Terrain::TerrainHandler &handler = this->dataModel.GetWorld()->GetTerrainHandler();
    Graphics::TerrainDrawer::DrawTerrain(handler, drawBegin);
}

void GameStandalone::DrawActors(const Game::Vector2 &drawBegin)
{
    Game::World *world = this->dataModel.GetWorld();
    ALLEGRO_COLOR player_col = al_map_rgb(0, 255, 255);

    Graphics::ActorDrawer::DrawActor(world, this->player, drawBegin, player_col);
}

void GameStandalone::HandleKeyDown(int keycode)
{
    bool is_controlling_character = (this->player != nullptr);
    if (is_controlling_character)
    {
        if (keycode == ALLEGRO_KEY_UP)
        {
            this->player_controller->Jump();
        }
        else if (keycode == ALLEGRO_KEY_LEFT)
        {
            this->player_controller->Move(Game::Actor::Direction::Left);
        }
        else if (keycode == ALLEGRO_KEY_RIGHT)
        {
            this->player_controller->Move(Game::Actor::Direction::Right);
        }
    }
}

void GameStandalone::HandleKeyUp(int keycode)
{
    bool is_controlling_character = (this->player != nullptr);
    if (is_controlling_character)
    {
        ALLEGRO_KEYBOARD_STATE keyboardState;
        al_get_keyboard_state(&keyboardState);
        if (keycode == ALLEGRO_KEY_LEFT)
        {
            this->player_controller->StopMoving(Game::Actor::Direction::Left);
            if (al_key_down(&keyboardState, ALLEGRO_KEY_RIGHT))
            {
                this->player_controller->Move(Game::Actor::Direction::Right);
            }
        }
        else if (keycode == ALLEGRO_KEY_RIGHT)
        {
            this->player_controller->StopMoving(Game::Actor::Direction::Right);
            if (al_key_down(&keyboardState, ALLEGRO_KEY_LEFT))
            {
                this->player_controller->Move(Game::Actor::Direction::Left);
            }
        }
    }
}

void GameStandalone::CreatePlayerForClient()
{
    Game::PlayerList *playerList = this->dataModel.GetPlayerList();
    Game::Player *player = new Game::Player();
    player->SetNetworkOwner(0);
    playerList->AddPlayer(player);
    this->dataModel.GetWorld()->AddActor(player);

    this->player = player;
    this->player_controller = new Input::PlayerController(this->player, this->dataModel.GetWorld());

    this->log->LogMessage("Created new player for this client\n", Util::LogLevel::Info);
}
