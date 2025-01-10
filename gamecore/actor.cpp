#include "actor.hpp"

namespace Game
{

Actor::Actor() : size(Vector2(40, 80)), position(Vector2(0, 200)), velocity(), direction(Actor::Direction::Left), jump_power(300), walkspeed(100)
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

void Actor::SetDirection(Direction dir)
{
    this->direction = dir;
}

void Actor::SetPosition(const Vector2 &pos)
{
    this->position = pos;
}


void Actor::SetVelocity(const Vector2 &vel)
{
    this->velocity = vel;
}

void Actor::AddVelocity(const Vector2 &vel)
{
    this->velocity += vel;
}

void Actor::Update(double deltaT)
{
    this->position += (this->velocity * deltaT);
}

bool Actor::IsOnGround() const
{
    bool y_velocity_is_zero = (this->GetVelocity().y == 0);
    return y_velocity_is_zero;
}

void Actor::Jump()
{
    this->AddVelocity(Vector2(0, this->jump_power));
}

void Actor::SetPhysicsSettings(const PhysicsSettings &settings)
{
    this->SetJumpPower(settings.GetDefaultJumpPower());
    this->SetWalkspeed(settings.GetDefaultWalkspeed());
}


void Actor::SetJumpPower(double power)
{
    if (power > 0)
        this->jump_power = power;
    else
        this->jump_power = 0;
}

double Actor::GetJumpPower() const
{
    return this->jump_power;
}

void Actor::SetWalkspeed(double speed)
{
    if (speed > 0)
        this->walkspeed = speed;
    else
        this->walkspeed = 0;
}

double Actor::GetWalkspeed() const
{
    return this->walkspeed;
}

}

