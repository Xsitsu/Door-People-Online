#ifndef PHYSICSHANDLER_HPP_INCLUDE
#define PHYSICSHANDLER_HPP_INCLUDE

#include "gamecore_dll_export.h"

#include "physicssettings.hpp"
#include "physicsobject.hpp"

#include "resourcemanager.hpp"

namespace Game::Physics
{

typedef res_handle phys_obj_handle;

class DLL_EXPORT PhysicsHandler
{
public:
    PhysicsHandler();
    virtual ~PhysicsHandler();

    phys_obj_handle CreatePhysicsObject();
    void DestroyPhysicsObject(const phys_obj_handle &handle);
    PhysicsObject* GetPhysicsObject(const phys_obj_handle &handle);

    const PhysicsSettings& GetPhysicsSettings() const;
    void SetPhysicsSettings(const PhysicsSettings& settings);

    void Tick(const double &deltaT);

protected:
    PhysicsSettings settings;
    ResourceManager<PhysicsObject> physics_objects;
};

}


#endif // PHYSICSHANDLER_HPP_INCLUDE