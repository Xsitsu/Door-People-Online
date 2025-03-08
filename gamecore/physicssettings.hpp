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

    int GetGravity() const;
    int GetDefaultWalkspeed() const;
    int GetDefaultJumpPower() const;

public:
    int gravity;
    int default_walkspeed;
    int default_jump_power;

};

}

#endif // PHYSICS_SETTINGS_HPP_INCLUDE
