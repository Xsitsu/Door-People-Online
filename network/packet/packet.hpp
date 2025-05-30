#ifndef PACKET_HPP_INCLUDE
#define PACKET_HPP_INCLUDE

#include "network_dll_export.h"

#include <string>

#include "address.hpp"

namespace Network
{

enum PacketFamily : uint8_t
{
    FAMILY_NONE = 0,
    FAMILY_CONNECT = 1,
    FAMILY_DISCONNECT = 2,
    FAMILY_TERRAIN = 3,
    FAMILY_PLAYER = 4,
    FAMILY_PHYSICS_SETTINGS = 5,
};

enum PacketAction : uint8_t
{
    ACTION_NONE = 0,
    ACTION_REQUEST = 1,
    ACTION_ACCEPT = 2,
    ACTION_DECLINE = 3,
    ACTION_TELL = 4,
    ACTION_ADD = 5,
    ACTION_REMOVE = 6,
};

std::string PacketFamilyToString(PacketFamily family);
std::string PacketActionToString(PacketAction action);

namespace Packet
{

class DLL_EXPORT Base
{
public:
    Base(uint32_t conId, PacketAction action);
    virtual ~Base();
    virtual unsigned int GetPacketSize() const;

    uint32_t GetConnectionId() const;
    virtual PacketFamily GetFamily() const = 0;
    PacketAction GetAction() const;

    virtual void Encode(void *&data) const;
    virtual void Decode(unsigned int packet_size, void *&data);

    std::string ToStr() const;

protected:
    std::string ToStrHeader() const;
    std::string ToStrFooter() const;
    virtual std::string ToStrBody() const;

protected:
    uint32_t connectionId;
    PacketAction action;
};

}

}

#endif // PACKET_HPP_INCLUDE
