#include "physicssettings.hpp"

#include <sstream>

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

std::string PhysicsSettings::ToStr() const
{
    std::stringstream ss;
    ss << "PhysicsSettings(";
    ss << "Gravity=" << this->gravity << ", ";
    ss << "DefaultWalkspeed=" << this->default_walkspeed << ", ";
    ss << "DefaultJumpPower=" << this->default_jump_power;
    ss << ")";
    return ss.str();
}

}