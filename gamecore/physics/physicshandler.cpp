#include "physicshandler.hpp"

#include <cstring>

namespace Game::Physics
{

PhysicsHandler::PhysicsHandler() : max_physics_objects(0), availability(), physics_objects(nullptr)
{

}

PhysicsHandler::~PhysicsHandler()
{

}

phys_obj_handle PhysicsHandler::CreatePhysicsObject()
{
    return 0;
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

    for (int i = 0; i < this->max_physics_objects; i++)
    {
        PhysicsObject &obj = this->physics_objects[i];
        obj.AddVelocity(gravity_update);
        
    }

    for (auto &obj : this->objects)
    {
        obj.AddPosition(obj.GetVelocity() * deltaT);
    }
}

void PhysicsHandler::ReserveSpace(int num_items)
{
    bool needs_to_grow = (this->availability.size() < num_items);
    if (needs_to_grow)
    {
        this->availability.reserve(num_items);
        for (int i = this->max_physics_objects; i < num_size; i++)
        {
            this->availability[i] = true;
        }

        PhysicsObject *new_data = new PhysicsObject[num_items];
        memcpy(new_data, this->physics_objects, sizeof(PhysicsObject) * this->max_physics_objects);

        delete[] this->physics_objects;
        this->physics_objects = new_data;
        this->max_physics_objects = num_items;
    }
}


}