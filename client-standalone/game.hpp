#ifndef GAME_HPP_INCLUDE
#define GAME_HPP_INCLUDE

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_native_dialog.h"

#include "gamecore/datamodel.hpp"
#include "gamecore/player.hpp"

#include "util/log/logger.hpp"

#include "input/playercontroller.hpp"

class GameStandalone
{
public:
    GameStandalone();
    ~GameStandalone();

    void Run();

protected:
    void DrawTerrain(const Game::Vector2 &drawBegin);

    void HandleKeyDown(int keycode);
    void HandleKeyUp(int keycode);

protected:
    void CreatePlayerForClient();

    // ALLEGRO Variables
protected:
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timer;

    // Game variables
protected:
    Game::DataModel dataModel;
    bool isRunning;

    Input::PlayerController* player_controller;
    Game::Player *player;

    // Log stuff
protected:
    Util::Log* log;

};

#endif // GAME_HPP_INCLUDE