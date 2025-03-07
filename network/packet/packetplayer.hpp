#ifndef PACKETPLAYER_HPP_INCLUDE
#define PACKETPLAYER_HPP_INCLUDE

#include "network_dll_export.h"

#include <list>

#include "packet.hpp"

namespace Network
{

namespace Packet
{

class DLL_EXPORT Player : public Packet::Base
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

    virtual PacketFamily GetFamily() const;

    virtual void Encode(void *data) const;
    virtual void Decode(unsigned int packet_size, void *data);
    
    const std::list<PlayerData>& GetPlayerData() const;
    void AddPlayerData(PlayerData data);

protected:
    virtual std::string ToStrBody() const;

protected:
    std::list<PlayerData> playerData;

};

}

}

#endif // PACKETPLAYER_HPP_INCLUDE
