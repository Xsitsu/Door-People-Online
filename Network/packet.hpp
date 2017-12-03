#ifndef PACKET_HPP_INCLUDE
#define PACKET_HPP_INCLUDE

#include "main.h"

#include <string>

namespace Network
{

enum PacketFamily : uint8_t
{
    FAMILY_NONE = 0,
    FAMILY_CONNECT = 1,
};

enum PacketAction : uint8_t
{
    ACTION_NONE = 0,
    ACTION_REQUEST = 1,
    ACTION_ACCEPT = 2,
    ACTION_DECLINE = 3,
    ACTION_CORRECT = 4,
};

std::string PacketFamilyToString(PacketFamily family);
std::string PacketActionToString(PacketAction action);

namespace Packet
{

#ifdef _WIN32
class DLL_EXPORT Base
#else
class Base
#endif // _WIN32
{
public:
    Base(uint32_t conId, PacketFamily family, PacketAction action);
    virtual ~Base();
    virtual unsigned int GetPacketSize() const;

    uint32_t GetConnectionId() const;
    PacketFamily GetFamily() const;
    PacketAction GetAction() const;

protected:
    uint32_t connectionId;
    PacketFamily family;
    PacketAction action;
};

}

}

#endif // PACKET_HPP_INCLUDE
