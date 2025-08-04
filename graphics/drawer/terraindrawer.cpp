#include "terraindrawer.hpp"

namespace Graphics
{

TerrainDrawer::TerrainDrawer()
{}

TerrainDrawer::~TerrainDrawer()
{}

void TerrainDrawer::DrawTerrain(const Game::Terrain::TerrainHandler &handler, const Game::Vector2 &drawBegin)
{
    const Game::ResourceManager<Game::Terrain::TerrainObject> &platforms = handler.GetPlatforms();
    for (Game::res_handle handle = 0; handle < platforms.CurNumResources(); handle++)
    {
        TerrainDrawer::DrawGeneric(platforms.GetResource(handle), drawBegin, al_map_rgb(20, 20, 220));
    }

    const Game::ResourceManager<Game::Terrain::TerrainObject> &walls = handler.GetWalls();
    for (Game::res_handle handle = 0; handle < platforms.CurNumResources(); handle++)
    {
        TerrainDrawer::DrawGeneric(walls.GetResource(handle), drawBegin, al_map_rgb(20, 220, 20));
    }
}

void TerrainDrawer::DrawGeneric(const Game::Terrain::TerrainObject *obj, const Game::Vector2 &drawBegin, ALLEGRO_COLOR col)
{
    Game::Vector2 size = obj->GetGameObject().size;
    Game::Vector2 position = obj->GetGameObject().position;

    Game::Vector2 posAdder(position.x, -position.y);

    Game::Vector2 drawStart = drawBegin + posAdder;
    Game::Vector2 drawEnd = drawStart + size;
    al_draw_filled_rectangle(drawStart.x, drawStart.y, drawEnd.x, drawEnd.y, col);
}

}
