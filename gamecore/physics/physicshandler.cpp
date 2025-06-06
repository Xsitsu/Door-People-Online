#include "physicshandler.hpp"

#include <cstring>

namespace Game::Physics
{

PhysicsHandler::PhysicsHandler() : physics_objects()
{

}

PhysicsHandler::~PhysicsHandler()
{

}

phys_obj_handle PhysicsHandler::CreatePhysicsObject()
{
    return this->physics_objects.CreateResource();
}

void PhysicsHandler::DestroyPhysicsObject(const phys_obj_handle &handle)
{
    this->physics_objects.DestroyResource(handle);
}

PhysicsObject* PhysicsHandler::GetPhysicsObject(const phys_obj_handle &handle)
{
    return this->physics_objects.GetResource(handle);
}

void PhysicsHandler::Tick(const double &deltaT)
{
    Vector2 gravity_update = Vector2(0, this->settings.gravity * deltaT);

    for (int i = 0; i < this->physics_objects.MaxNumResources(); i++)
    {
        PhysicsObject *obj = this->physics_objects.GetResource(i);
        if (obj != nullptr)
        {
            obj->AddVelocity(gravity_update);
        }
    }
}

}