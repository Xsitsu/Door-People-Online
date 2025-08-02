#ifndef TERRAINDRAWER_HPP_INCLUDE
#define TERRAINDRAWER_HPP_INCLUDE

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"

#include "gamecore/terrain/terrainhandler.hpp"
#include "gamecore/vector2.hpp"

class TerrainDrawer
{
public:
    static void DrawTerrain(const Game::Terrain::Terrainhandler &handler, const Game::Vector2 &drawBegin);

protected:
    TerrainDrawer();
    ~TerrainDrawer();

protected:
    static void DrawGeneric(const Game::Terrain::TerrainObject *obj, const Game::Vector2 &drawBegin, ALLEGRO_COLOR col);

};

#endif // TERRAINDRAWER_HPP_INCLUDE
