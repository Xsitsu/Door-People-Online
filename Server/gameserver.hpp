#ifndef GAMESERVER_HPP_INCLUDE
#define GAMESERVER_HPP_INCLUDE

#include "network/server.hpp"
#include "network/packetall.hpp"

#include "gamecore/datamodel.hpp"

class GameServer : public Network::Server
{
public:
    GameServer();
    virtual ~GameServer();

protected:
    Game::DataModel datamodel;

};

#endif // GAMESERVER_HPP_INCLUDE
