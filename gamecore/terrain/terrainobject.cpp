#include "terrain.hpp"

namespace Game::Terrain
{

TerrainObject::Terrain() : game_object()
{

}

TerrainObject::~Terrain()
{

}

const GameObject& GetGameObject() const
{
    return this->game_object;
}

void SetGameObject(const GameObject &obj)
{
    this->game_object = obj;
}

}
