#ifndef WALL_HPP_INCLUDE
#define WALL_HPP_INCLUDE

#include "gamecore_dll_export.h"

#include "terrain.hpp"

namespace Game
{

class DLL_EXPORT Wall : public Terrain
{
public:
    Wall();
    virtual ~Wall();

protected:

};

}

#endif // WALL_HPP_INCLUDE
