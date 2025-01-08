#ifndef PHYSICS_SETTINGS_HPP_INCLUDE
#define PHYSICS_SETTINGS_HPP_INCLUDE

#include "gamecore_dll_export.h"

#include "vector2.hpp"

namespace Game
{

class DLL_EXPORT PhysicsSettings
{
public:
    PhysicsSettings();

    double GetGravity() const;
    double GetDefaultWalkspeed() const;
    double GetDefaultJumpPower() const;

public:
    double gravity;
    double default_walkspeed;
    double default_jump_power;

};

}

#endif // PHYSICS_SETTINGS_HPP_INCLUDE
