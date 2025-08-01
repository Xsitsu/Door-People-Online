#ifndef PHYSICSOBJECT_HPP_INCLUDE
#define PHYSICSOBJECT_HPP_INCLUDE

#include "gamecore_dll_export.h"

#include "vector2.hpp"
#include "gameobject/gameobject.hpp"

namespace Game::Physics
{

class DLL_EXPORT PhysicsObject
{
public:
    const Vector2& GetVelocity() const;
    void SetVelocity(const Vector2 &val);
    void AddVelocity(const Vector2 &val);

    const GameObject& GetGameObject() const;
    void UpdatePosition(const Vector2 &val);


protected:
    Vector2 velocity;
    GameObject game_object;
};

}

#endif // PHYSICSOBJECT_HPP_INCLUDE