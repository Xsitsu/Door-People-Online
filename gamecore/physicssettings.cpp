#include "physicssettings.hpp"

namespace Game
{

PhysicsSettings::PhysicsSettings()
{
    this->gravity = 960;
    this->default_walkspeed = 360;
    this->default_jump_power = 320;
}

double PhysicsSettings::GetGravity() const
{
    return this->gravity;
}

double PhysicsSettings::GetDefaultWalkspeed() const
{
    return this->default_walkspeed;
}

double PhysicsSettings::GetDefaultJumpPower() const
{
    return this->default_jump_power;
}


}