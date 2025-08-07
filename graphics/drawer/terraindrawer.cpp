#include "terraindrawer.hpp"

namespace Graphics
{

TerrainDrawer::TerrainDrawer()
{}

TerrainDrawer::~TerrainDrawer()
{}

void TerrainDrawer::DrawTerrain(const Game::Terrain::TerrainHandler &handler, const Game::Vector2 &drawBegin)
{
    ALLEGRO_COLOR platform_col = al_map_rgb(20, 20, 220);
    ALLEGRO_COLOR wall_col = al_map_rgb(20, 220, 20);

    TerrainDrawer::DrawAllInResourceHandler(handler.GetPlatforms(), drawBegin, platform_col);
    TerrainDrawer::DrawAllInResourceHandler(handler.GetWalls(), drawBegin, wall_col);
}

void TerrainDrawer::DrawAllInResourceHandler(const Game::ResourceManager<Game::Terrain::TerrainObject> &handler, const Game::Vector2 &drawBegin, const ALLEGRO_COLOR &col)
{
    for (Game::res_handle handle = 0; handle < handler.MaxNumResources(); handle++)
    {
        if (handler.ResourceExists(handle))
            TerrainDrawer::DrawGeneric(handler.GetResource(handle), drawBegin, col);
    }
}



void TerrainDrawer::DrawGeneric(const Game::Terrain::TerrainObject *obj, const Game::Vector2 &drawBegin, const ALLEGRO_COLOR &col)
{
    const Game::Vector2 &size = obj->GetGameObject().size;
    const Game::Vector2 &position = obj->GetGameObject().position;

    Game::Vector2 posAdder(position.x, -position.y);

    Game::Vector2 drawStart = drawBegin + posAdder;
    Game::Vector2 drawEnd = drawStart + size;
    al_draw_filled_rectangle(drawStart.x, drawStart.y, drawEnd.x, drawEnd.y, col);
}

}
