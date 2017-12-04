#include "packetbuilder.hpp"

#include "network/packetall.hpp"

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
    PacketFamily family = packet->GetFamily();
    PacketAction action = packet->GetAction();

    PacketBuilder::Put32(data, packet->GetConnectionId());
    PacketBuilder::PutFamily(data, family);
    PacketBuilder::PutAction(data, action);

    if (family == PacketFamily::FAMILY_CONNECT)
    {
        Packet::Connect *pkt = static_cast<Packet::Connect*>(packet);
        PacketBuilder::Put32(data, pkt->GetAssignedId());
    }
    else if (family == PacketFamily::FAMILY_DISCONNECT)
    {
        //Packet::Disconnect *pkt = static_cast<Packet::Disconnect*>(packet);
        // nothing else required
    }
}

void PacketBuilder::PacketBuilder::PutFamily(void *&data, PacketFamily value)
{
    PacketFamily *d = static_cast<PacketFamily*>(data);
    *d = value;
    d++;
    data = d;
}

void PacketBuilder::PutAction(void *&data, PacketAction value)
{
    PacketAction *d = static_cast<PacketAction*>(data);
    *d = value;
    d++;
    data = d;
}

void PacketBuilder::Put32(void *&data, uint32_t value)
{
    uint32_t *d = static_cast<uint32_t*>(data);
    *d = htonl(value);
    d++;
    data = d;
}

void PacketBuilder::Put16(void *&data, uint16_t value)
{
    uint16_t *d = static_cast<uint16_t*>(data);
    *d = htons(value);
    d++;
    data = d;
}

void PacketBuilder::Put8(void *&data, uint8_t value)
{
    uint8_t *d = static_cast<uint8_t*>(data);
    *d = value;
    d++;
    data = d;
}

}
