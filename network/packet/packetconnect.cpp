#include "packetconnect.hpp"

#include "packetbuilder.hpp"
#include "packetreader.hpp"

namespace Network
{

namespace Packet
{

Connect::Connect(uint32_t conId, PacketAction action) : Packet::Base(conId, action), assignedId(0)
{

}

Connect::~Connect()
{

}

unsigned int Connect::GetPacketSize() const
{
    return sizeof(uint32_t) + Packet::Base::GetPacketSize();
}

PacketFamily Connect::GetFamily() const
{
    return PacketFamily::FAMILY_CONNECT;
}

void Connect::Encode(void *data) const
{
    Packet::Base::Encode(data);
    PacketBuilder::Put32(data, this->GetAssignedId());
}

void Connect::Decode(unsigned int packet_size, void *data)
{
    Packet::Base::Decode(packet_size, data);
    this->SetAssignedId(PacketReader::Read32(data));
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
