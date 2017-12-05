#ifndef WORLD_HPP_INCLUDE
#define WORLD_HPP_INCLUDE

#include "main.h"

#include <list>

#include "Util/service.hpp"

#include "vector2.hpp"
#include "actor.hpp"
#include "terrain.hpp"
#include "platform.hpp"
#include "wall.hpp"

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
    virtual ~World();

    Vector2 GetGravity() const;
    void SetGravity(const Vector2 &gravity);

    void Update(double deltaT);

    void AddActor(Actor *actor);
    void RemoveActor(Actor *actor);
    std::list<Actor*> GetActors();

    void LoadWorld();
    void ClearTerrain();
    void AddTerrain(Terrain *terrain);
    std::list<Terrain*> GetTerrain();

    bool IsTerrainLoaded() const;
    void SetTerrainIsLoaded(bool loaded);

protected:
    bool SegmentsOverlap(double x1, double x2, double y1, double y2) const;

    Vector2 gravity;
    std::list<Actor*> actors;
    std::list<Terrain*> terrain;

    bool terrainIsLoaded;

};

}

#endif // WORLD_HPP_INCLUDE
