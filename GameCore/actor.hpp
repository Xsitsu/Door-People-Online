#ifndef ACTOR_HPP_INCLUDE
#define ACTOR_HPP_INCLUDE

#include "GameCore_dll-export.h"

#include "vector2.hpp"

namespace Game
{

class DLL_EXPORT Actor
{
public:
    enum Direction
    {
        DIR_LEFT,
        DIR_RIGHT
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

    void Jump();

protected:
    Vector2 size;
    Vector2 position;
    Vector2 velocity;
    Direction direction;

};

}

#endif // ACTOR_HPP_INCLUDE
