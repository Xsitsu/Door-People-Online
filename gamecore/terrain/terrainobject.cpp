#include "terrainobject.hpp"

namespace Game::Terrain
{

TerrainObject::TerrainObject() : game_object()
{

}

TerrainObject::~TerrainObject()
{

}

const GameObject& TerrainObject::GetGameObject() const
{
    return this->game_object;
}

void TerrainObject::SetGameObject(const GameObject &obj)
{
    this->game_object = obj;
}

}
