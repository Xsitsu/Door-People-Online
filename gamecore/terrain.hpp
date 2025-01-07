#ifndef TERRAIN_HPP_INCLUDE
#define TERRAIN_HPP_INCLUDE

#include "gamecore_dll_export.h"

#include "vector2.hpp"

namespace Game
{

enum TerrainType
{
    TYPE_PLATFORM = 1,
    TYPE_WALL = 2,
};

class DLL_EXPORT Terrain
{
public:
    Terrain(TerrainType type);
    virtual ~Terrain();

    TerrainType GetTerrainType() const;
    Vector2 GetPosition() const;
    Vector2 GetSize() const;

    void SetPosition(const Vector2 &position);
    void SetSize(const Vector2 &size);

protected:
    TerrainType type;
    Vector2 position;
    Vector2 size;
};

}

#endif // TERRAIN_HPP_INCLUDE
