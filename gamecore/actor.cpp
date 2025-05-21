#include "actor.hpp"

namespace Game
{

Actor::Actor() : phys_obj(nullptr), direction(Actor::Direction::Left), jump_power(300), walkspeed(100)
{

}

Actor::~Actor()
{

}

bool Actor::IsPlayer() const
{
    return false;
}

Actor::Direction Actor::GetDirection() const
{
    return this->direction;
}

void Actor::SetDirection(Direction dir)
{
    this->direction = dir;
}

bool Actor::IsOnGround() const
{
    bool y_velocity_is_zero = (this->phys_obj->GetVelocity().y == 0);
    return y_velocity_is_zero;
}

void Actor::Jump()
{
    this->phys_obj->AddVelocity(Vector2(0, this->jump_power));
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

