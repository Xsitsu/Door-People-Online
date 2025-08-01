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

void LoadTerrTerrainHandler::ain(std::string terrain_data)
{

}

void TerrainHandler::UnloadTerrain()
{

}


}