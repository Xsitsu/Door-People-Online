#include "packetbuilder.hpp"

#include "network/packet/packetall.hpp"

namespace Network
{

PacketBuilder::PacketBuilder()
{

}

PacketBuilder::~PacketBuilder()
{

}

void PacketBuilder::BuildPacket(Packet::Base *packet, void *data)
{
    packet->Encode(data);
}

const void PacketBuilder::PacketBuilder::PutFamily(void *&data, PacketFamily value)
{
    PacketFamily *d = static_cast<PacketFamily*>(data);
    *d = value;
    d++;
    data = d;
}

const void PacketBuilder::PutAction(void *&data, PacketAction value)
{
    PacketAction *d = static_cast<PacketAction*>(data);
    *d = value;
    d++;
    data = d;
}

const void PacketBuilder::Put32(void *&data, uint32_t value)
{
    uint32_t *d = static_cast<uint32_t*>(data);
    *d = htonl(value);
    d++;
    data = d;
}

const void PacketBuilder::Put16(void *&data, uint16_t value)
{
    uint16_t *d = static_cast<uint16_t*>(data);
    *d = htons(value);
    d++;
    data = d;
}

const void PacketBuilder::Put8(void *&data, uint8_t value)
{
    uint8_t *d = static_cast<uint8_t*>(data);
    *d = value;
    d++;
    data = d;
}

}
