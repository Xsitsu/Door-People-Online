#ifndef PHYSICSOBJECT_HPP_INCLUDE
#define PHYSICSOBJECT_HPP_INCLUDE

#include "gamecore_dll_export.h"

#include "vector2.hpp"

namespace Game::Physics
{

class DLL_EXPORT PhysicsObject
{
public:
    const Vector2& GetVelocity() const;
    void SetVelocity(const Vector2 &val);
    void AddVelocity(const Vector2 &val);

protected:
    Vector2 velocity;
};

}

#endif // PHYSICSOBJECT_HPP_INCLUDE