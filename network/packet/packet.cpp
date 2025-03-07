#include "packet.hpp"

#include "packetbuilder.hpp"
#include "packetreader.hpp"

#include <cstring>

namespace Network
{

std::string PacketFamilyToString(PacketFamily family)
{
    switch (family)
    {
    case PacketFamily::FAMILY_NONE:
        return "FAMILY_NONE";

    case PacketFamily::FAMILY_CONNECT:
        return "FAMILY_CONNECT";

    case PacketFamily::FAMILY_DISCONNECT:
        return "FAMILY_DISCONNECT";

    case PacketFamily::FAMILY_TERRAIN:
        return "FAMILY_TERRAIN";

    case PacketFamily::FAMILY_PLAYER:
        return "FAMILY_PLAYER";

    default:
        return "N/A";
    }
}

std::string PacketActionToString(PacketAction action)
{
    switch (action)
    {
    case PacketAction::ACTION_NONE:
        return "ACTION_NONE";

    case PacketAction::ACTION_REQUEST:
        return "ACTION_REQUEST";

    case PacketAction::ACTION_ACCEPT:
        return "ACTION_ACCEPT";

    case PacketAction::ACTION_DECLINE:
        return "ACTION_DECLINE";

    case PacketAction::ACTION_TELL:
        return "ACTION_TELL";

    case PacketAction::ACTION_ADD:
        return "ACTION_ADD";

    case PacketAction::ACTION_REMOVE:
        return "ACTION_REMOVE";

    default:
        return "N/A";
    }
}

namespace Packet
{

Base::Base(uint32_t conId, PacketAction action) : connectionId(conId), action(action)
{

}

Base::~Base()
{

}

unsigned int Base::GetPacketSize() const
{
    return sizeof(uint32_t) + sizeof(PacketFamily) + sizeof(PacketAction);
}

uint32_t Base::GetConnectionId() const
{
    return this->connectionId;
}

PacketAction Base::GetAction() const
{
    return this->action;
}

void Base::Encode(void *data) const
{
    PacketBuilder::Put32(data, this->GetConnectionId());
    PacketBuilder::PutFamily(data, this->GetFamily());
    PacketBuilder::PutAction(data, this->GetAction());
}

void Base::Decode(unsigned int packet_size, void *data)
{
    //uint32_t connectionId = PacketReader::Read32(data);
    //PacketFamily family = PacketReader::ReadFamily(data);
    //PacketAction action = PacketReader::ReadAction(data);
}

}

}
