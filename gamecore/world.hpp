#ifndef WORLD_HPP_INCLUDE
#define WORLD_HPP_INCLUDE

#include "gamecore_dll_export.h"

#include <list>

#include "util/service.hpp"

#include "actor.hpp"

#include "physics/physicshandler.hpp"
#include "terrain/terrainhandler.hpp"

namespace Game
{

class DLL_EXPORT World : public Util::Service
{
public:
    World();
    virtual ~World();

    void Update(double deltaT);

    void AddActor(Actor *actor);
    void RemoveActor(Actor *actor);
    std::list<Actor*> GetActors();

    Physics::PhysicsHandler& GetPhysicsHandler();
    Terrain::TerrainHandler& GetTerrainHandler();

protected:
    bool SegmentsOverlap(double x1, double x2, double y1, double y2) const;

    void UpdatePhysics(double deltaT);
    void ResolveCollisions(double deltaT);

    void ResolveCollisionsForSingle(double deltaT, Game::Physics::PhysicsObject *obj, const ResourceManager<Game::Terrain::TerrainObject> &objects);


    Physics::PhysicsHandler physics_handler;
    Terrain::TerrainHandler terrain_handler;

    std::list<Actor*> actors;

};

}

#endif // WORLD_HPP_INCLUDE
