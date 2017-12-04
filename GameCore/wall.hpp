#ifndef WALL_HPP_INCLUDE
#define WALL_HPP_INCLUDE

#include "main.h"

#include "terrain.hpp"

namespace Game
{

#ifdef _WIN32
class DLL_EXPORT Wall : public Terrain
#else
class Wall : public Terrain
#endif // _WIN32
{
public:
    Wall();
    virtual ~Wall();

protected:

};

}

#endif // WALL_HPP_INCLUDE
