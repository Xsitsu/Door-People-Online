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
    virtual void ClientConnectionAdded(Network::ClientConnection *connection);
    virtual void ClientConnectionRemoving(Network::ClientConnection *connection);

    bool HandlePacket(Network::Packet::Terrain *packet, const Network::Address &sender);

    Game::DataModel dataModel;

    bool isRunning;

};

#endif // GAMESERVER_HPP_INCLUDE
