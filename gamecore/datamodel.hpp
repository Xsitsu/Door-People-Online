#ifndef DATAMODEL_HPP_INCLUDE
#define DATAMODEL_HPP_INCLUDE

#include "gamecore_dll_export.h"

#include "util/serviceprovider.hpp"

#include "world.hpp"
#include "playerlist.hpp"

namespace Game
{

class DLL_EXPORT DataModel : public Util::ServiceProvider
{
public:
    DataModel();
    virtual ~DataModel();
    virtual void Init();

    World* GetWorld();
    PlayerList* GetPlayerList();

protected:

};

}

#endif // DATAMODEL_HPP_INCLUDE