#include "world.hpp"

#include <stdio.h>

namespace Game
{

World::World() : actors(), terrain(), terrainIsLoaded(false)
{

}

World::~World()
{

}


void World::Update(double deltaT)
{
    this->UpdatePhysics(deltaT);
    this->ResolveCollisions(deltaT);

/*
    if (!this->actors.empty())
    {
        for (auto actor : this->actors)
        {
            Vector2 size = actor->GetSize();
            Vector2 before = actor->GetPosition();

            if (before.y < -300)
            {
                actor->SetPosition(Vector2(0, 300));
                before = actor->GetPosition();
                actor->AddVelocity(Vector2(0, -actor->GetVelocity().y));
            }

            Vector2 addGrav(0, -this->physics_settings.gravity);
            actor->AddVelocity(addGrav * deltaT);
            actor->Update(deltaT);
            Vector2 after = actor->GetPosition();

            Vector2 delta = after - before;
            Vector2 velocity = actor->GetVelocity();

            for (Terrain *tObj : this->terrain)
            {
                Vector2 objPos = tObj->GetPosition();
                Vector2 objSize = tObj->GetSize();

                Vector2 topRight(objPos.x + objSize.x, objPos.y);
                Vector2 bottomLeft(objPos.x, objPos.y - objSize.y);
                Vector2 bottomRight(topRight.x, bottomLeft.y);

                if (tObj->GetTerrainType() == TerrainType::TYPE_PLATFORM)
                {
                    if (velocity.y < 0 && this->SegmentsOverlap(after.x, after.x + size.x, objPos.x, topRight.x))
                    {
                        if (before.y - size.y >= objPos.y)
                        {
                            if (objPos.y > (after.y - size.y))
                            {
                                after.y = objPos.y + size.y;
                                velocity.y = 0;
                            }
                        }
                    }
                }
                else if (tObj->GetTerrainType() == TerrainType::TYPE_WALL)
                {
                    if (this->SegmentsOverlap(after.x, after.x + size.x, objPos.x, topRight.x))
                    {
                        if (velocity.y < 0)
                        {
                            if (before.y - size.y >= objPos.y)
                            {
                                if (objPos.y > (after.y - size.y))
                                {
                                    after.y = objPos.y + size.y;
                                    velocity.y = 0;
                                }
                            }
                        }
                        else if (velocity.y > 0)
                        {
                            if (bottomLeft.y >= before.y)
                            {
                                if (after.y > bottomLeft.y)
                                {
                                    after.y = bottomLeft.y;
                                    //velocity.y = 0;
                                }
                            }
                        }
                    }

                    if (this->SegmentsOverlap(after.y - size.y, after.y, bottomLeft.y, objPos.y))
                    {
                        if (velocity.x > 0)
                        {
                            if (objPos.x >= before.x + size.x)
                            {
                                if (after.x + size.x > objPos.x)
                                {
                                    after.x = objPos.x - size.x;
                                }
                            }
                        }
                        else if (velocity.x < 0)
                        {
                            if (topRight.x <= before.x)
                            {
                                if (after.x < topRight.x)
                                {
                                    after.x = topRight.x;
                                }
                            }
                        }
                    }
                }
            }

            actor->SetPosition(after);
            actor->SetVelocity(velocity);
        }
    }
*/
}

void World::UpdatePhysics(double deltaT)
{
    this->physics_handler.Tick(deltaT);
}

void World::ResolveCollisions(double deltaT)
{

}


void World::AddActor(Actor *actor)
{
    Physics::phys_obj_handle handle = this->physics_handler.CreatePhysicsObject();
    actor->SetPhysicsObjectHandle(handle);
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

bool World::SegmentsOverlap(double x1, double x2, double y1, double y2) const
{
    return (x2 > y1 && y2 > x1);
}

}
