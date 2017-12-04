#ifndef ACTOR_HPP_INCLUDE
#define ACTOR_HPP_INCLUDE

#include "main.h"

#include "vector2.hpp"

namespace Game
{

#ifdef _WIN32
class DLL_EXPORT Actor
#else
class Actor
#endif // _WIN32
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

    Vector2 GetPosition() const;
    Vector2 GetVelocity() const;
    Direction GetDirection() const;

    void AddVelocity(const Vector2 &vel);
    void Update(double deltaT);

    void Jump();

protected:
    Vector2 position;
    Vector2 velocity;
    Direction direction;

};

}

#endif // ACTOR_HPP_INCLUDE
