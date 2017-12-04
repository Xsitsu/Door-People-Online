#include "actor.hpp"

namespace Game
{

Actor::Actor() : size(Vector2(40, 80)), position(), velocity(), direction(Actor::Direction::DIR_LEFT)
{

}

Actor::~Actor()
{

}

bool Actor::IsPlayer() const
{
    return false;
}

Vector2 Actor::GetSize() const
{
    return this->size;
}

Vector2 Actor::GetPosition() const
{
    return this->position;
}

Vector2 Actor::GetVelocity() const
{
    return this->velocity;
}

Actor::Direction Actor::GetDirection() const
{
    return this->direction;
}

void Actor::AddVelocity(const Vector2 &vel)
{
    this->velocity += vel;
}

void Actor::Update(double deltaT)
{
    this->position += (this->velocity * deltaT);
}

void Actor::Jump()
{
    this->AddVelocity(Vector2(0, 80));
}

}

