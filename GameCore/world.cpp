#include "world.hpp"

#include <iostream>

namespace Game
{

World::World() : gravity(), actors()
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


}
