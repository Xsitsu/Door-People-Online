#ifndef ACTORDRAWER_HPP_INCLUDE
#define ACTORDRAWER_HPP_INCLUDE

#include "graphics_dll_export.h"

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"

#include "gamecore/actor.hpp"
#include "gamecore/player.hpp"
#include "gamecore/vector2.hpp"
#include "gamecore/world.hpp"

namespace Graphics
{

class DLL_EXPORT ActorDrawer
{
public:
    static void DrawActor(Game::World *world, Game::Actor *actor, const Game::Vector2 &drawBegin, ALLEGRO_COLOR col);

protected:
    ActorDrawer();
    ~ActorDrawer();

};

}

#endif // ACTORDRAWER_HPP_INCLUDE
