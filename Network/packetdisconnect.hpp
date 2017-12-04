#ifndef PACKETDISCONNECT_HPP_INCLUDE
#define PACKETDISCONNECT_HPP_INCLUDE

#include "main.h"

#include "packet.hpp"

namespace Network
{

namespace Packet
{

#ifdef _WIN32
class DLL_EXPORT Disconnect : public Packet::Base
#else
class Disconnect : public Packet::Base
#endif // _WIN32
{
public:
    Disconnect(uint32_t conId, PacketAction action);
    virtual ~Disconnect();
    virtual unsigned int GetPacketSize() const;

protected:

};

}

}

#endif // PACKETDISCONNECT_HPP_INCLUDE
