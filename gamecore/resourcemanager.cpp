#include "resourcemanager.hpp"

namespace Game
{

template <typename T>
ResourceManager<T>::ResourceManager() : cur_num_resources(0), max_num_resources(0), availability(), resources(nullptr)
{

}

template <typename T>
ResourceManager<T>::~ResourceManager()
{
    // TODO: Free memory and reset default values
    // tbh not sure if there's a use case that will ever require this
}

template <typename T>
res_handle ResourceManager<T>::CreateResource()
{
    int look_index = 0;
    if (this->cur_num_resources == this->max_num_resources)
    {
        look_index = this->max_num_resources;
        int new_size = (this->max_num_resources * 2) + 10;
        this->ReserveSpace(new_size);
    }

    // TODO: Make allocation not O(n)
    while (this->availability[look_index] == true)
        look_index++;
    
    this->availability[look_index] = false;
    this->cur_num_resources++;

    return look_index;
}

template <typename T>
void ResourceManager<T>::DestroyResource(const res_handle &handle)
{
    if (this->HandleIsInRange(handle) && this->ResourceExists(handle))
    {
        this->availability[handle] = true;
        this->cur_num_resources--;
    }
}

template <typename T>
T* ResourceManager<T>::GetResource(const res_handle &handle)
{
    if (this->HandleIsInRange(handle) && this->ResourceExists(handle))
        return this->resources + handle;
    return nullptr;
}

template <typename T>
bool ResourceManager<T>::ResourceExists(const res_handle &handle)
{
    return (this->availability[handle] == false);
}

template <typename T>
bool ResourceManager<T>::HandleIsInRange(const res_handle &handle)
{
    return (handle >= 0 && handle < this->max_num_resources);
}

template <typename T>
void ResourceManager<T>::ReserveSpace(int num_items)
{
    bool needs_to_grow = (this->availability.size() < num_items);
    if (needs_to_grow)
    {
        this->availability.reserve(num_items);
        for (int i = this->max_num_resources; i < num_items; i++)
        {
            this->availability[i] = true;
        }

        T *new_data = new T[num_items];
        if (this->resources != nullptr)
        {
            memcpy(new_data, this->resources, sizeof(T) * this->max_num_resources);
            delete[] this->resources;
        }

        this->resources = new_data;
        this->max_num_resources = num_items;
    }
}

}