#ifndef CLIENT_HPP_INCLUDE
#define CLIENT_HPP_INCLUDE

#include "Network_dll-export.h"

#include "networkpeer.hpp"

#include "util/log/logger.hpp"

namespace Network
{

class DLL_EXPORT Client : public NetworkPeer
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
    virtual bool HandlePacket(Packet::Player *packet, const Address &sender);

    Address serverAddress;
    bool isConnected;
    uint32_t connectionId;

    Util::Log* log;
};

}


#endif // CLIENT_HPP_INCLUDE
