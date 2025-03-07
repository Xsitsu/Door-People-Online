#include "packetdisconnect.hpp"

namespace Network
{

namespace Packet
{

Disconnect::Disconnect(uint32_t conId, PacketAction action) : Packet::Base(conId, action)
{

}

Disconnect::~Disconnect()
{

}

unsigned int Disconnect::GetPacketSize() const
{
    return Packet::Base::GetPacketSize();
}

PacketFamily Disconnect::GetFamily() const
{
    return PacketFamily::FAMILY_DISCONNECT;
}

void Disconnect::Encode(void *data) const
{
    Packet::Base::Encode(data);
}

void Disconnect::Decode(unsigned int packet_size, void *data)
{
    Packet::Base::Decode(packet_size, data);
}

}

}
