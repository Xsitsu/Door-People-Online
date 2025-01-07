#ifndef TERRAINDRAWER_HPP_INCLUDE
#define TERRAINDRAWER_HPP_INCLUDE

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"

#include "gamecore/terrain.hpp"
#include "gamecore/platform.hpp"
#include "gamecore/wall.hpp"
#include "gamecore/vector2.hpp"

class TerrainDrawer
{
public:
    static void DrawTerrain(Game::Terrain *terrain, const Game::Vector2 &drawBegin, ALLEGRO_COLOR col);

protected:
    TerrainDrawer();
    ~TerrainDrawer();

};

#endif // TERRAINDRAWER_HPP_INCLUDE
