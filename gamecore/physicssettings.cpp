#include "physicssettings.hpp"

namespace Game
{

PhysicsSettings::PhysicsSettings()
{
    this->gravity = 960;
    this->default_walkspeed = 180;
    this->default_jump_power = 320;
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