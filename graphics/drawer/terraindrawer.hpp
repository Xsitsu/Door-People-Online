#ifndef TERRAINDRAWER_HPP_INCLUDE
#define TERRAINDRAWER_HPP_INCLUDE

#include "graphics_dll_export.h"

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"

#include "gamecore/terrain/terrainhandler.hpp"
#include "gamecore/vector2.hpp"

namespace Graphics
{

class TerrainDrawer
{
public:
    static void DrawTerrain(const Game::Terrain::TerrainHandler &handler, const Game::Vector2 &drawBegin);

protected:
    TerrainDrawer();
    ~TerrainDrawer();

protected:
    static void DrawAllInResourceHandler(const Game::ResourceManager<Game::Terrain::TerrainObject> &handler, const Game::Vector2 &drawBegin, const ALLEGRO_COLOR &col);
    static void DrawGeneric(const Game::Terrain::TerrainObject *obj, const Game::Vector2 &drawBegin, const ALLEGRO_COLOR &col);

};

}

#endif // TERRAINDRAWER_HPP_INCLUDE
