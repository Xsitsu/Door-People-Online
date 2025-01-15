#include "packetdisconnect.hpp"

namespace Network
{

namespace Packet
{

Disconnect::Disconnect(uint32_t conId, PacketAction action) : Packet::Base(conId, PacketFamily::FAMILY_DISCONNECT, action)
{

}

Disconnect::~Disconnect()
{

}

unsigned int Disconnect::GetPacketSize() const
{
    return Packet::Base::GetPacketSize();
}

}

}
