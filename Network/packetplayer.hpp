#ifndef PACKETPLAYER_HPP_INCLUDE
#define PACKETPLAYER_HPP_INCLUDE

#include "main.h"

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
    Player(uint32_t conId, PacketAction action);
    virtual ~Player();
    virtual unsigned int GetPacketSize() const;

    uint32_t GetPlayerId() const;
    void SetPlayerId(uint32_t id);

    uint8_t GetDir() const;
    uint32_t GetPosX() const;
    uint32_t GetPosY() const;
    uint32_t GetVelX() const;
    uint32_t GetVelY() const;

    void SetDir(uint8_t val);
    void SetPosX(uint32_t val);
    void SetPosY(uint32_t val);
    void SetVelX(uint32_t val);
    void SetVelY(uint32_t val);


protected:
    uint32_t playerId;
    uint8_t dir;
    uint32_t posX;
    uint32_t posY;
    uint32_t velX;
    uint32_t velY;

};

}

}

#endif // PACKETPLAYER_HPP_INCLUDE
