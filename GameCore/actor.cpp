#include "actor.hpp"

namespace Game
{

Actor::Actor() : position(), velocity(), direction(Actor::Direction::DIR_LEFT)
{

}

Actor::~Actor()
{

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

