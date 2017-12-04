#ifndef GAMESERVER_HPP_INCLUDE
#define GAMESERVER_HPP_INCLUDE

#include "network/server.hpp"
#include "network/packetall.hpp"

#include "gamecore/datamodel.hpp"

#include "util/timer.hpp"

class GameServer : public Network::Server
{
public:
    GameServer();
    virtual ~GameServer();

    void Run();

protected:
    Game::DataModel dataModel;

    bool isRunning;

};

#endif // GAMESERVER_HPP_INCLUDE
