#ifndef ACTORDRAWER_HPP_INCLUDE
#define ACTORDRAWER_HPP_INCLUDE

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"

#include "gamecore/actor.hpp"
#include "gamecore/player.hpp"
#include "gamecore/vector2.hpp"

class ActorDrawer
{
public:
    static void DrawActor(Game::Actor *actor, const Game::Vector2 &drawBegin, ALLEGRO_COLOR col);

protected:
    ActorDrawer();
    ~ActorDrawer();

};

#endif // ACTORDRAWER_HPP_INCLUDE
