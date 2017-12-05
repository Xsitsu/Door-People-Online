#ifndef DATAMODEL_HPP_INCLUDE
#define DATAMODEL_HPP_INCLUDE

#include "main.h"

#include "Util/serviceprovider.hpp"

#include "world.hpp"
#include "playerlist.hpp"

namespace Game
{

#ifdef _WIN32
class DLL_EXPORT DataModel : public Util::ServiceProvider
#else
class DataModel : public Util::ServiceProvider
#endif // _WIN32
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
