#include "world.hpp"

#include <stdio.h>

namespace Game
{

World::World() : actors()
{

}

World::~World()
{

}


void World::Update(double deltaT)
{
    this->UpdatePhysics(deltaT);
    this->ResolveCollisions(deltaT);
}

void World::UpdatePhysics(double deltaT)
{
    this->physics_handler.Tick(deltaT);
}

void World::ResolveCollisions(double deltaT)
{
    for (Game::Physics::phys_obj_handle handle = 0; handle < this->GetPhysicsHandler().MaxNumPhysicsObject(); handle++)
    {
        Game::Physics::PhysicsObject *obj = this->GetPhysicsHandler().GetPhysicsObject(handle);
        if (obj != nullptr)
        {
            this->ResolveCollisionsForSingle(deltaT, obj, this->GetTerrainHandler().GetWalls());
            if (obj->GetVelocity().y < 0)
            {
                this->ResolveCollisionsForSingle(deltaT, obj, this->GetTerrainHandler().GetPlatforms());
            }
        }
    }
}

void World::ResolveCollisionsForSingle(double deltaT, Game::Physics::PhysicsObject *obj, const ResourceManager<Game::Terrain::TerrainObject> &objects)
{
    Game::Vector2 position_before = obj->GetGameObject().position - (obj->GetVelocity() * deltaT);
    Game::Vector2 position_now = obj->GetGameObject().position;
    Game::Vector2 size = obj->GetGameObject().size;

    for (Game::Terrain::terrain_obj_handle handle = 0; handle < objects.MaxNumResources(); handle++)
    {
        const Game::Terrain::TerrainObject *t_obj = objects.GetResource(handle);
        if (t_obj != nullptr)
        {
            // Collide Down
            if (obj->IsMovingDown())
            {
                double edge_bottom_before = position_before.y - size.y;
                double edge_bottom_now = position_now.y - size.y;

                const Game::Vector2 &pos = t_obj->GetGameObject().position;
                const Game::Vector2 &t_size = t_obj->GetGameObject().size;
                Game::Vector2 t_bounds = pos + t_size;

                if (edge_bottom_before >= pos.y && edge_bottom_now < pos.y)
                {
                    double edge_left_now = position_now.x;
                    double edge_right_now = position_now.x + size.x;
                    if (edge_left_now < t_bounds.x && edge_right_now > pos.x)
                    {
                        obj->GetGameObject().position.y = pos.y + size.y;
                        obj->SetVelocity(Vector2(obj->GetVelocity().x, 0));
                    }
                }

            }
        }
    }

}

void World::AddActor(Actor *actor)
{
    Physics::phys_obj_handle handle = this->physics_handler.CreatePhysicsObject();
    actor->SetPhysicsObjectHandle(handle);

    Game::GameObject &obj = this->physics_handler.GetPhysicsObject(handle)->GetGameObject();
    obj.size = Game::Vector2(40, 80);
    obj.position = Game::Vector2(0, 200);

    auto settings = this->GetPhysicsHandler().GetPhysicsSettings();
    actor->SetJumpPower(settings.GetDefaultJumpPower());
    actor->SetWalkspeed(settings.GetDefaultWalkspeed());

    this->actors.push_back(actor);
}

void World::RemoveActor(Actor *actor)
{
    Physics::phys_obj_handle handle = actor->GetPhysicsObjectHandle();
    if (handle != -1)
    {
        actor->SetPhysicsObjectHandle(-1);
        this->physics_handler.DestroyPhysicsObject(handle);
    }

    this->actors.remove(actor);
}

std::list<Actor*> World::GetActors()
{
    return this->actors;
}

Physics::PhysicsHandler& World::GetPhysicsHandler()
{
    return this->physics_handler;
}


Terrain::TerrainHandler& World::GetTerrainHandler()
{
    return this->terrain_handler;
}


bool World::SegmentsOverlap(double x1, double x2, double y1, double y2) const
{
    return (x2 > y1 && y2 > x1);
}

}
