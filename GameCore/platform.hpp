#ifndef PLATFORM_HPP_INCLUDE
#define PLATFORM_HPP_INCLUDE

#include "GameCore_dll-export.h"

#include "terrain.hpp"

namespace Game
{
class DLL_EXPORT Platform : public Terrain
{
public:
    Platform();
    virtual ~Platform();

protected:

};

}

#endif // PLATFORM_HPP_INCLUDE
