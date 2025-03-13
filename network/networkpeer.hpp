#ifndef NETWORKPEER_HPP_INCLUDE
#define NETWORKPEER_HPP_INCLUDE

#include "network_dll_export.h"

#include "socket.hpp"
#include "packet/packetall.hpp"

namespace Network
{

class DLL_EXPORT NetworkPeer
{
public:
    NetworkPeer();
    virtual ~NetworkPeer();

    Packet::Base* ReceivePacket(Address &sender);
    void SendPacket(Packet::Base* packet, const Address &destination);

protected:
    bool DoHandlePacket(Packet::Base *packet, const Address &sender);
    virtual bool HandlePacket(Packet::Base *packet, const Address &sender) = 0;
    virtual bool HandlePacket(Packet::Connect *packet, const Address &sender) = 0;
    virtual bool HandlePacket(Packet::Disconnect *packet, const Address &sender) = 0;
    virtual bool HandlePacket(Packet::Terrain *packet, const Address &sender) = 0;
    virtual bool HandlePacket(Packet::Player *packet, const Address &sender) = 0;
    virtual bool HandlePacket(Packet::PhysicsSettings *packet, const Address &sender) = 0;

    Socket socket;
};

}

#endif // NETWORKPEER_HPP_INCLUDE
