#ifndef SERVER_HPP_INCLUDE
#define SERVER_HPP_INCLUDE

#include "main.h"

#include <unordered_map>

#include "networkpeer.hpp"
#include "clientconnection.hpp"
#include "packetall.hpp"

namespace Network
{

#ifdef _WIN32
class DLL_EXPORT Server : public NetworkPeer
#else
class Server : public NetworkPeer
#endif // _WIN32
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
    virtual bool HandlePacket(Packet::Base *packet, const Address &sender);
    virtual bool HandlePacket(Packet::Connect *packet, const Address &sender);
    virtual bool HandlePacket(Packet::Disconnect *packet, const Address &sender);
    virtual bool HandlePacket(Packet::Terrain *packet, const Address &sender);

    uint32_t conIdCounter;
    unsigned int maxClients;
    std::unordered_map<uint32_t, ClientConnection*> connections;
    std::unordered_map<unsigned int, unsigned int> connectionsPerAddr;
};

}

#endif // SERVER_HPP_INCLUDE
