#ifndef TERRAIN_OBJECT_HPP_INCLUDE
#define TERRAIN_OBJECT_HPP_INCLUDE

#include "gamecore_dll_export.h"

#include "gameobject/gameobject.hpp"

namespace Game::Terrain
{

class DLL_EXPORT TerrainObject
{
public:
    TerrainObject();
    virtual ~TerrainObject();

    const GameObject& GetGameObject() const;
    void SetGameObject(const GameObject &obj);

protected:
    GameObject game_object;
};

}

#endif // TERRAIN_OBJECT_HPP_INCLUDE
