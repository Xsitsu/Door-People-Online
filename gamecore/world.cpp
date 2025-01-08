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

void World::SetPhysicsSettings(const PhysicsSettings &settings)
{
    this->physics_settings = settings;
}

void World::Update(double deltaT)
{
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
}

void World::AddActor(Actor *actor)
{
    actor->SetPhysicsSettings(this->physics_settings);
    this->actors.push_back(actor);
}

void World::RemoveActor(Actor *actor)
{
    this->actors.remove(actor);
}

std::list<Actor*> World::GetActors()
{
    return this->actors;
}

void World::LoadWorld()
{
    Terrain *terrainObj;

    terrainObj = new Platform();
    terrainObj->SetSize(Vector2(800, 20));
    terrainObj->SetPosition(Vector2(-300, 0));
    this->AddTerrain(terrainObj);

    terrainObj = new Wall();
    terrainObj->SetSize(Vector2(40, 200));
    terrainObj->SetPosition(Vector2(-300, 200));
    this->AddTerrain(terrainObj);

    terrainObj = new Wall();
    terrainObj->SetSize(Vector2(40, 200));
    terrainObj->SetPosition(Vector2(460, 200));
    this->AddTerrain(terrainObj);

    for (int i = 0; i < 4; i++)
    {
        terrainObj = new Platform();
        int s = 60 * (5-i);
        terrainObj->SetSize(Vector2(s, 20));
        terrainObj->SetPosition(Vector2(460 - s, 40 * (i + 1)));
        this->AddTerrain(terrainObj);
    }

    terrainObj = new Platform();
    terrainObj->SetSize(Vector2(600, 20));
    terrainObj->SetPosition(Vector2(500, 200));
    this->AddTerrain(terrainObj);

    this->SetTerrainIsLoaded(true);
}

void World::ClearTerrain()
{
    for (Terrain *terrainObj : this->terrain)
    {
        delete terrainObj;
    }

    this->terrain.clear();
}

void World::AddTerrain(Terrain *terrain)
{
    this->terrain.push_back(terrain);
}

std::list<Terrain*> World::GetTerrain()
{
    return this->terrain;
}

bool World::IsTerrainLoaded() const
{
    return this->terrainIsLoaded;
}

void World::SetTerrainIsLoaded(bool loaded)
{
    this->terrainIsLoaded = loaded;
}

bool World::SegmentsOverlap(double x1, double x2, double y1, double y2) const
{
    return (x2 > y1 && y2 > x1);
}

}
