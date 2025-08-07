#include "terrainhandler.hpp"

namespace Game::Terrain
{

TerrainHandler::TerrainHandler()
{

}

TerrainHandler::~TerrainHandler()
{

}

const ResourceManager<TerrainObject>& TerrainHandler::GetWalls() const
{
    return this->walls;
}

const ResourceManager<TerrainObject>& TerrainHandler::GetPlatforms() const
{
    return this->platforms;
}

void TerrainHandler::LoadTerrain(std::string terrain_data)
{

}

void TerrainHandler::UnloadTerrain()
{

}

bool TerrainHandler::TerrainIsLoaded() const
{
    return (this->walls.CurNumResources() > 0 || this->platforms.CurNumResources() > 0);
}


void TerrainHandler::CreateTerrainObject(ResourceManager<TerrainObject>& res, const GameObject &obj)
{
    res_handle handle = res.CreateResource();
    res.GetResource(handle)->SetGameObject(obj);
}


void TerrainHandler::LoadMockTerrain()
{
    // GameObject(position, size)

    // Platforms
    this->CreateTerrainObject(this->platforms, GameObject(Vector2(-300, 0), Vector2(800, 20)));

    for (int i = 0; i < 4; i++)
    {
        int s = 60 * (5-i);
        this->CreateTerrainObject(this->platforms, GameObject(Vector2(460 - s, 40 * (i + 1)), Vector2(s, 20)));
    }

    this->CreateTerrainObject(this->platforms, GameObject(Vector2(500, 200), Vector2(600, 20)));


    // Walls
    this->CreateTerrainObject(this->walls, GameObject(Vector2(-300, 200), Vector2(40, 200)));
    this->CreateTerrainObject(this->walls, GameObject(Vector2(460, 200), Vector2(40, 200)));


}


}