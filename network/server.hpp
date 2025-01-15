#ifndef SERVER_HPP_INCLUDE
#define SERVER_HPP_INCLUDE

#include "network_dll_export.h"

#include <unordered_map>

#include "networkpeer.hpp"
#include "clientconnection.hpp"
#include "packet/packetall.hpp"

#include "util/log/logger.hpp"

namespace Network
{

class DLL_EXPORT Server : public NetworkPeer
{
public:
    Server();
    virtual ~Server();

    bool Init(unsigned short port, unsigned int maxClients);
    void Tick();
    void Shutdown();

    unsigned int NumConnectionsOnAddr(uint32_t addr) const;

    bool HasConnection(uint32_t conId) const;
    ClientConnection* GetConnection(uint32_t conId);
    ClientConnection* GetConnectionFromAddress(const Address &address);
    void AddConnection(uint32_t conId, const Address &address);
    void RemoveConnection(uint32_t conId);

protected:
    virtual void ClientConnectionAdded(ClientConnection *connection);
    virtual void ClientConnectionRemoving(ClientConnection *connection);

    virtual bool HandlePacket(Packet::Base *packet, const Address &sender);
    virtual bool HandlePacket(Packet::Connect *packet, const Address &sender);
    virtual bool HandlePacket(Packet::Disconnect *packet, const Address &sender);
    virtual bool HandlePacket(Packet::Terrain *packet, const Address &sender);
    virtual bool HandlePacket(Packet::Player *packet, const Address &sender);

    uint32_t conIdCounter;
    unsigned int maxClients;
    std::unordered_map<uint32_t, ClientConnection*> connections;
    std::unordered_map<unsigned int, unsigned int> connectionsPerAddr;

    Util::Log* log;
};

}

#endif // SERVER_HPP_INCLUDE
