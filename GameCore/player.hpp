#ifndef PLAYER_HPP_INCLUDE
#define PLAYER_HPP_INCLUDE

#include "main.h"

#include <string> // uint32_t

#include "actor.hpp"

namespace Game
{

#ifdef _WIN32
class DLL_EXPORT Player : public Actor
#else
class Player : public Actor
#endif // _WIN32
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
