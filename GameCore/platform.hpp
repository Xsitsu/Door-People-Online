#ifndef PLATFORM_HPP_INCLUDE
#define PLATFORM_HPP_INCLUDE

#include "main.h"

#include "terrain.hpp"

namespace Game
{

#ifdef _WIN32
class DLL_EXPORT Platform : public Terrain
#else
class Platform : public Terrain
#endif // _WIN32
{
public:
    Platform();
    virtual ~Platform();

protected:

};

}

#endif // PLATFORM_HPP_INCLUDE
