#ifndef PACKETCONNECT_HPP_INCLUDE
#define PACKETCONNECT_HPP_INCLUDE

#include "network_dll_export.h"

#include "packet.hpp"

namespace Network
{

namespace Packet
{

class DLL_EXPORT Connect : public Packet::Base
{
public:
    Connect(uint32_t conId, PacketAction action);
    virtual ~Connect();
    virtual unsigned int GetPacketSize() const;

    virtual PacketFamily GetFamily() const;

    virtual void Encode(void *data) const;
    virtual void Decode(unsigned int packet_size, void *data);

    uint32_t GetAssignedId() const;
    void SetAssignedId(uint32_t id);

protected:
    uint32_t assignedId;
};

}

}

#endif // PACKETCONNECT_HPP_INCLUDE
