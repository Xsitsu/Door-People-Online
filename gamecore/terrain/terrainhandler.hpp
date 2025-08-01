#ifndef TERRAIN_HANDLER_HPP_INCLUDE
#define TERRAIN_HANDLER_HPP_INCLUDE

#include "gamecore_dll_export.h"

#include "resourcemanager.hpp"
#include "terrainobject.hpp"

namespace Game::Terrain
{

typedef res_handle terrain_obj_handle;

class DLL_EXPORT TerrainHandler
{
public:
    TerrainHandler();
    virtual ~TerrainHandler();

    const ResourceManager<TerrainObject>& GetWalls() const;
    const ResourceManager<TerrainObject>& GetPlatforms() const;

    void LoadTerrain(std::string terrain_data);
    void UnloadTerrain();

private:
    ResourceManager<TerrainObject> walls;
    ResourceManager<TerrainObject> platforms;

};

}

#endif // TERRAIN_HANDLER_HPP_INCLUDE
