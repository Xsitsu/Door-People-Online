#ifndef ACTOR_HPP_INCLUDE
#define ACTOR_HPP_INCLUDE

#include "gamecore_dll_export.h"

#include "vector2.hpp"

#include "physics/physicshandler.hpp"
#include "physics/physicsobject.hpp"

namespace Game
{

class DLL_EXPORT Actor
{
public:
    enum class Direction : int
    {
        Left = -1,
        None = 0,
        Right = 1,
    };

public:
    Actor();
    virtual ~Actor();

    virtual bool IsPlayer() const;

    Direction GetDirection() const;
    void SetDirection(Direction dir);

    bool IsOnGround() const;
    void Jump();

    void SetJumpPower(double power);
    double GetJumpPower() const;

    void SetWalkspeed(double speed);
    double GetWalkspeed() const;

    Physics::phys_obj_handle GetPhysicsObjectHandle() const;
    void SetPhysicsObjectHandle(Physics::phys_obj_handle handle);

protected:
    Physics::PhysicsObject* GetPhysicsObject();
    const Physics::PhysicsObject* GetPhysicsObject() const;

protected:
    Direction direction;
    Physics::phys_obj_handle physics_object;

    double jump_power;
    double walkspeed;

};

}

#endif // ACTOR_HPP_INCLUDE
