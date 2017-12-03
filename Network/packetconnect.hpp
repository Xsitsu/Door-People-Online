#ifndef PACKETCONNECT_HPP_INCLUDE
#define PACKETCONNECT_HPP_INCLUDE

#include "main.h"

#include "packet.hpp"

namespace Network
{

namespace Packet
{

#ifdef _WIN32
class DLL_EXPORT Connect : public Packet::Base
#else
class Connect : public Packet::Base
#endif // _WIN32
{
public:
    Connect(uint32_t conId, PacketFamily family, PacketAction action);
    virtual ~Connect();
    virtual unsigned int GetPacketSize() const;

    uint32_t GetAssignedId() const;
    void SetAssignedId(uint32_t id);

protected:
    uint32_t assignedId;
};

}

}

#endif // PACKETCONNECT_HPP_INCLUDE
