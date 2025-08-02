#include "terraindrawer.hpp"

TerrainDrawer::TerrainDrawer()
{}

TerrainDrawer::~TerrainDrawer()
{}

void TerrainDrawer::DrawTerrain(const Game::Terrain::Terrainhandler &handler, const Game::Vector2 &drawBegin)
{
    const ResourceManager<TerrainObject> &platforms = handler.GetPlatforms();
    for (res_handle handle = 0; handle < platforms.CurNumResources(); handle++)
    {
        this->DrawGeneric(platforms.GetResource(handle), drawBegin, al_map_rg(20, 20, 220))
    }

    const ResourceManager<TerrainObject> &walls = handler.GetWalls();
    for (res_handle handle = 0; handle < walls.CurNumResources(); handle++)
    {
        this->DrawGeneric(walls.GetResource(handle), drawBegin, al_map_rg(20, 220, 20))
    }
}

void TerrainDrawer::DrawGeneric(const Game::Terrain::TerrainObject *obj, const Game::Vector2 &drawBegin, ALLEGRO_COLOR col)
{
    Game::Vector2 size = terrain->GetGameObject().size;
    Game::Vector2 position = terrain->GetGameObject().position();

    Game::Vector2 posAdder(position.x, -position.y);

    Game::Vector2 drawStart = drawBegin + posAdder;
    Game::Vector2 drawEnd = drawStart + size;
    al_draw_filled_rectangle(drawStart.x, drawStart.y, drawEnd.x, drawEnd.y, col);
}
