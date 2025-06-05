#include "actor.hpp"

namespace Game
{

Actor::Actor() : direction(Actor::Direction::Left), jump_power(300), walkspeed(100), physics_object(-1)
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
    bool y_velocity_is_zero = (this->GetPhysicsObject()->GetVelocity().y == 0);
    return y_velocity_is_zero;
}

void Actor::Jump()
{
    this->GetPhysicsObject()->AddVelocity(Vector2(0, this->jump_power));
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

Physics::phys_obj_handle Actor::GetPhysicsObjectHandle() const
{
    return this->physics_object;
}

void Actor::SetPhysicsObjectHandle(Physics::phys_obj_handle handle)
{
    this->physics_object = handle;
}


Physics::PhysicsObject* Actor::GetPhysicsObject()
{
    return nullptr;
}

const Physics::PhysicsObject* Actor::GetPhysicsObject() const
{
    return nullptr;
}

}

