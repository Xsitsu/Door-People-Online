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

const GameObject& PhysicsObject::GetGameObject() const
{
    return this->game_object;
}

GameObject& PhysicsObject::GetGameObject()
{
    return this->game_object;
}

void PhysicsObject::UpdatePosition(const Vector2 &val)
{
    this->game_object.position += val;
}


}
