#include "world.hpp"

namespace Game
{

World::World() : gravity(), actors(), terrain()
{
    this->SetGravity(Vector2(0, -20));
}

World::~World()
{

}

Vector2 World::GetGravity() const
{
    return this->gravity;
}

void World::SetGravity(const Vector2 &gravity)
{
    this->gravity = gravity;
}

void World::Update(double deltaT)
{
    if (!this->actors.empty())
    {
        for (auto actor : this->actors)
        {
            actor->AddVelocity(this->gravity);
            actor->Update(deltaT);
        }
    }
}

void World::AddActor(Actor *actor)
{
    this->actors.push_back(actor);
}

void World::RemoveActor(Actor *actor)
{
    this->actors.remove(actor);
}

void World::LoadWorld()
{
    Terrain *terrainObj;

    terrainObj = new Platform();
    terrainObj->SetSize(Vector2(400, 20));
    terrainObj->SetPosition(Vector2(-200, 0));
    this->AddTerrain(terrainObj);

    terrainObj = new Wall();
    terrainObj->SetSize(Vector2(40, 200));
    terrainObj->SetPosition(Vector2(-200, -200));
    this->AddTerrain(terrainObj);

    terrainObj = new Platform();
    terrainObj->SetSize(Vector2(600, 20));
    terrainObj->SetPosition(Vector2(300, -20));
    this->AddTerrain(terrainObj);
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

}
