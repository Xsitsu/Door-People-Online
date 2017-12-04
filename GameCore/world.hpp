#ifndef WORLD_HPP_INCLUDE
#define WORLD_HPP_INCLUDE

#include "main.h"

#include <list>

#include "util/service.hpp"

#include "vector2.hpp"
#include "actor.hpp"

namespace Game
{

#ifdef _WIN32
class DLL_EXPORT World : public Util::Service
#else
class World : public Util::Service
#endif // _WIN32
{
public:
    World();
    ~World();

    Vector2 GetGravity() const;
    void SetGravity(const Vector2 &gravity);

    void Update(double deltaT);

    void AddActor(Actor *actor);
    void RemoveActor(Actor *actor);

protected:
    Vector2 gravity;
    std::list<Actor*> actors;

};

}

#endif // WORLD_HPP_INCLUDE
