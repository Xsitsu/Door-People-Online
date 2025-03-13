#ifndef PACKETDISCONNECT_HPP_INCLUDE
#define PACKETDISCONNECT_HPP_INCLUDE

#include "network_dll_export.h"

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

    virtual PacketFamily GetFamily() const;

    virtual void Encode(void *&data) const;
    virtual void Decode(unsigned int packet_size, void *&data);

protected:

};

}

}

#endif // PACKETDISCONNECT_HPP_INCLUDE
