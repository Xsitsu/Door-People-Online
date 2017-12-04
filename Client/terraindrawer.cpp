#include "terraindrawer.hpp"

#include <iostream>

TerrainDrawer::TerrainDrawer()
{

}

TerrainDrawer::~TerrainDrawer()
{

}

void TerrainDrawer::DrawTerrain(Game::Terrain *terrain, const Game::Vector2 &drawBegin, ALLEGRO_COLOR col)
{
    Game::Vector2 size = terrain->GetSize();
    Game::Vector2 position = terrain->GetPosition();

    Game::Vector2 posAdder(position.x, -position.y);

    Game::Vector2 drawStart = drawBegin + posAdder;
    Game::Vector2 drawEnd = drawStart + size;
    al_draw_filled_rectangle(drawStart.x, drawStart.y, drawEnd.x, drawEnd.y, col);
}
