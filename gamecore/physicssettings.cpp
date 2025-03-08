#include "physicssettings.hpp"

namespace Game
{

PhysicsSettings::PhysicsSettings()
{
    this->gravity = 100;
    this->default_walkspeed = 100;
    this->default_jump_power = 100;
}

int PhysicsSettings::GetGravity() const
{
    return this->gravity;
}

int PhysicsSettings::GetDefaultWalkspeed() const
{
    return this->default_walkspeed;
}

int PhysicsSettings::GetDefaultJumpPower() const
{
    return this->default_jump_power;
}


}