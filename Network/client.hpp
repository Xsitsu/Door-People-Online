#ifndef CLIENT_HPP_INCLUDE
#define CLIENT_HPP_INCLUDE

#include "main.h"

#include "networkpeer.hpp"

namespace Network
{

#ifdef _WIN32
class DLL_EXPORT Client : public NetworkPeer
#else
class Client : public NetworkPeer
#endif // _WIN32
{
public:
    Client();
    virtual ~Client();

    bool Init(unsigned short port);
    void Connect(const Address &serverAddress);
    bool IsConnected() const;
    void Disconnect();

    void Tick();

    const Address& GetServerAddress() const;
    uint32_t GetConnectionId() const;

protected:
    virtual bool HandlePacket(Packet::Base *packet, const Address &sender);
    virtual bool HandlePacket(Packet::Connect *packet, const Address &sender);
    virtual bool HandlePacket(Packet::Disconnect *packet, const Address &sender);
    virtual bool HandlePacket(Packet::Terrain *packet, const Address &sender);

    Address serverAddress;
    bool isConnected;
    uint32_t connectionId;
};

}


#endif // CLIENT_HPP_INCLUDE
