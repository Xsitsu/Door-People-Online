#include "packetconnect.hpp"

namespace Network
{

namespace Packet
{

Connect::Connect(uint32_t conId, PacketFamily family, PacketAction action) : Packet::Base(conId, family, action), assignedId(0)
{

}

Connect::~Connect()
{

}

unsigned int Connect::GetPacketSize() const
{
    return sizeof(uint32_t) + Packet::Base::GetPacketSize();
}

uint32_t Connect::GetAssignedId() const
{
    return this->assignedId;
}

void Connect::SetAssignedId(uint32_t id)
{
    this->assignedId = id;
}


}

}
