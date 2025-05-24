#include "physicshandler.hpp"

#include <cstring>

namespace Game::Physics
{

PhysicsHandler::PhysicsHandler() : cur_num_physics_objects(0), max_physics_objects(0), availability(), physics_objects(nullptr)
{

}

PhysicsHandler::~PhysicsHandler()
{

}

phys_obj_handle PhysicsHandler::CreatePhysicsObject()
{
    int look_index = 0;
    if (this->cur_num_physics_objects == this->max_physics_objects)
    {
        look_index = this->max_physics_objects;
        int new_size = (this->max_physics_objects * 2) + 10;
        this->ReserveSpace(new_size)
    }

    while (this->availability[look_index] == false)
        look_index++;

    this->availability[look_index] = true;
    this->cur_num_physics_objects++;

    return look_index;
}

void PhysicsHandler::DestroyPhysicsObject(const phys_obj_handle &handle)
{
    if (this->HandleInRange(handle))
    {
        if (this->availability[handle] == false)
        {
            this->availability[handle] = true;
            this->cur_num_physics_objects--;
        }
    }
}

PhysicsObject* PhysicsHandler::GetPhysicsObject(const phys_obj_handle &handle)
{
    if (this->HandleInRange(handle) && this->availability[handle])
        return this->physics_objects[handle];
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

bool PhysicsHandler::HandleInRange(const phys_obj_handle &handle)
{
    return (handle >= 0 && handle < this->max_physics_objects);
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