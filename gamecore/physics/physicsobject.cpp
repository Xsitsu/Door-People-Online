#include "physicsobject.hpp"

namespace Game::Physics
{

const Vector2& PhysicsObject::GetVelocity() const
{
    return this->velocity;
}

void PhysicsObject::SetVelocity(const Vector2 &val)
{
    this->velocity = val;
}

void PhysicsObject::AddVelocity(const Vector2 &val)
{
    this->velocity += val;
}

}
