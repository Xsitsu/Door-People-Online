#include "physicshandler.hpp"

namespace Game::Physics
{

PhysicsHandler::PhysicsHandler() : num_physics_objects(0), physics_objects(nullptr)
{

}

PhysicsHandler::~PhysicsHandler()
{

}

phys_obj_handle PhysicsHandler::CreatePhysicsObject()
{
    // Create a new element in the vector, and then return it as a pointer

    int last = this->objects.size();
    this->objects.resize(last + 1);
    return &(this->objects[last]);
}

void PhysicsHandler::DestroyPhysicsObject(const phys_obj_handle &handle)
{

}

PhysicsObject* PhysicsHandler::GetPhysicsObject(const phys_obj_handle &handle)
{
    return nullptr;
}


void PhysicsHandler::Tick(const double &deltaT)
{
    Vector2 gravity_update = Vector2(0, this->settings.gravity * deltaT);

    for (int i = 0; i < this->num_physics_objects; i++)
    {
        PhysicsObject &obj = this->physics_objects[i];
        obj.AddVelocity(gravity_update);
        
    }

    for (auto &obj : this->objects)
    {
        obj.AddPosition(obj.GetVelocity() * deltaT);
    }
}

}