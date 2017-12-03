#ifndef NETWORKPEER_HPP_INCLUDE
#define NETWORKPEER_HPP_INCLUDE

#include "main.h"

#include "socket.hpp"
#include "packet.hpp"

namespace Network
{

#ifdef _WIN32
class DLL_EXPORT NetworkPeer
#else
class NetworkPeer
#endif // _WIN32
{
public:
    NetworkPeer();
    virtual ~NetworkPeer();

    Packet::Base* ReceivePacket(Address &sender);
    void SendPacket(Packet::Base* packet, const Address &destination);

    void SetMaxPacketSize(unsigned int buffSize);

protected:
    Socket socket;

    unsigned int maxPacketSize;

};

}

#endif // NETWORKPEER_HPP_INCLUDE
