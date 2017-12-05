#include "packetplayer.hpp"

namespace Network
{

namespace Packet
{

Player::Player(uint32_t conId, PacketAction action) : Packet::Base(conId, PacketFamily::FAMILY_PLAYER, action), playerId(0), dir(0), posX(0),  posY(0), velX(0), velY(0)
{

}

Player::~Player()
{

}

unsigned int Player::GetPacketSize() const
{
    return sizeof(uint8_t) + (5 * sizeof(uint32_t)) + Packet::Base::GetPacketSize();
}

uint32_t Player::GetPlayerId() const
{
    return this->playerId;
}

void Player::SetPlayerId(uint32_t id)
{
    this->playerId = id;
}

uint8_t Player::GetDir() const
{
    return this->dir;
}

uint32_t Player::GetPosX() const
{
    return this->posX;
}

uint32_t Player::GetPosY() const
{
    return this->posY;
}

uint32_t Player::GetVelX() const
{
    return this->velX;
}

uint32_t Player::GetVelY() const
{
    return this->velY;
}

void Player::SetDir(uint8_t val)
{
    this->dir = val;
}

void Player::SetPosX(uint32_t val)
{
    this->posX = val;
}

void Player::SetPosY(uint32_t val)
{
    this->posY = val;
}

void Player::SetVelX(uint32_t val)
{
    this->velX = val;
}

void Player::SetVelY(uint32_t val)
{
    this->velY = val;
}

}

}
