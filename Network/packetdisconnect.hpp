#ifndef PACKETDISCONNECT_HPP_INCLUDE
#define PACKETDISCONNECT_HPP_INCLUDE

#include "Network_dll-export.h"

#include "packet.hpp"

namespace Network
{

namespace Packet
{

class DLL_EXPORT Disconnect : public Packet::Base
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
