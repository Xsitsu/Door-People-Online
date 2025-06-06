#ifndef RESOURCEHANDLER_HPP_INCLUDE
#define RESOURCEHANDLER_HPP_INCLUDE

#include "gamecore_dll_export.h"

#include <vector>

namespace Game
{

typedef int res_handle;

template <typename T>
class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    res_handle CreateResource();
    void DestroyResource(const res_handle &handle);
    T* GetResource(const res_handle &handle);
    bool ResourceExists(const res_handle &handle);
    int MaxNumResources() const;
    int CurNumResources() const;

private:
    bool HandleIsInRange(const res_handle &handle);
    void ReserveSpace(int num_items);

private:
    int cur_num_resources;
    int max_num_resources;
    std::vector<bool> availability;
    T* resources;
};

}

#endif // RESOURCEHANDLER_HPP_INCLUDE