#include "packet.hpp"

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

Base::Base(uint32_t conId, PacketFamily family, PacketAction action) : connectionId(conId), family(family), action(action)
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

PacketFamily Base::GetFamily() const
{
    return this->family;
}

PacketAction Base::GetAction() const
{
    return this->action;
}

}

}
