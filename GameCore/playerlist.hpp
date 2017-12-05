#ifndef PLAYERLIST_HPP_INCLUDE
#define PLAYERLIST_HPP_INCLUDE

#include <list>

#include "Util/service.hpp"

#include "player.hpp"

namespace Game
{

#ifdef _WIN32
class DLL_EXPORT PlayerList : public Util::Service
#else
class PlayerList : public Util::Service
#endif // _WIN32
{
public:
    PlayerList();
    virtual ~PlayerList();

    void AddPlayer(Player *player);
    void RemovePlayer(Player *player);
    std::list<Player*> GetPlayers();
    Player* GetPlayerWithNetworkId(uint32_t id);

protected:
    std::list<Player*> players;

};

}

#endif // PLAYERLIST_HPP_INCLUDE
