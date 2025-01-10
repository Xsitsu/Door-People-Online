#ifndef ACTOR_HPP_INCLUDE
#define ACTOR_HPP_INCLUDE

#include "gamecore_dll_export.h"

#include "vector2.hpp"
#include "physicssettings.hpp"

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

    Vector2 GetSize() const;
    Vector2 GetPosition() const;
    Vector2 GetVelocity() const;
    Direction GetDirection() const;

    void SetDirection(Direction dir);
    void SetPosition(const Vector2 &pos);
    void SetVelocity(const Vector2 &vel);
    void AddVelocity(const Vector2 &vel);
    void Update(double deltaT);

    bool IsOnGround() const;
    void Jump();

    void SetPhysicsSettings(const PhysicsSettings &settings);

    void SetJumpPower(double power);
    double GetJumpPower() const;

    void SetWalkspeed(double speed);
    double GetWalkspeed() const;

protected:
    Vector2 size;
    Vector2 position;
    Vector2 velocity;
    Direction direction;

    double jump_power;
    double walkspeed;

};

}

#endif // ACTOR_HPP_INCLUDE
