#ifndef GAMEOBJECT_HPP_INCLUDE
#define GAMEOBJECT_HPP_INCLUDE

#include "gamecore_dll_export.h"

#include "vector2.hpp"

namespace Game
{

struct DLL_EXPORT GameObject
{
    Vector2 position;
    Vector2 size;

    GameObject();
    GameObject(const Vector2 &position, const Vector2 &size);
};

}


#endif // GAMEOBJECT_HPP_INCLUDE