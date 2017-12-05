#ifndef PACKETPLAYER_HPP_INCLUDE
#define PACKETPLAYER_HPP_INCLUDE

#include "main.h"

#include <list>

#include "packet.hpp"

namespace Network
{

namespace Packet
{

#ifdef _WIN32
class DLL_EXPORT Player : public Packet::Base
#else
class Player : public Packet::Base
#endif // _WIN32
{
public:
    struct PlayerData
    {
        uint32_t playerId;
        uint8_t direction;
        uint32_t posX;
        uint32_t posY;
        uint32_t velX;
        uint32_t velY;
    };

    Player(uint32_t conId, PacketAction action);
    virtual ~Player();
    virtual unsigned int GetPacketSize() const;

    const std::list<PlayerData>& GetPlayerData() const;
    void AddPlayerData(PlayerData data);

protected:
    std::list<PlayerData> playerData;

};

}

}

#endif // PACKETPLAYER_HPP_INCLUDE
