#ifndef TRANSFORM_HPP_INCLUDE
#define TRANSFORM_HPP_INCLUDE

#include "gamecore_dll_export.h"

#include "vector2.hpp"

namespace Game
{

struct DLL_EXPORT Transform
{
    Vector2 position;
    Vector2 size;

    Transform();
};

}


#endif // TRANSFORM_HPP_INCLUDE