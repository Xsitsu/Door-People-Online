#ifndef PLAYER_HPP_INCLUDE
#define PLAYER_HPP_INCLUDE

#include "gamecore_dll_export.h"

#include <cstdint>

#include "actor.hpp"

namespace Game
{

class DLL_EXPORT Player : public Actor
{
public:
    Player();
    virtual ~Player();

    bool IsPlayer() const;

    uint32_t GetNetworkOwner() const;
    void SetNetworkOwner(uint32_t owner);

protected:
    uint32_t networkOwner;

};

}

#endif // PLAYER_HPP_INCLUDE
