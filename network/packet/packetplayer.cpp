#include "packetplayer.hpp"

namespace Network
{

namespace Packet
{

Player::Player(uint32_t conId, PacketAction action) : Packet::Base(conId, PacketFamily::FAMILY_PLAYER, action), playerData()
{

}

Player::~Player()
{

}

unsigned int Player::GetPacketSize() const
{
    int dataSize = sizeof(uint8_t) + (sizeof(uint32_t) * 5);
    int numData = this->playerData.size();
    return sizeof(uint8_t) + (dataSize * numData) + Packet::Base::GetPacketSize();
}

const std::list<Player::PlayerData>& Player::GetPlayerData() const
{
    return this->playerData;
}

void Player::AddPlayerData(PlayerData data)
{
    this->playerData.push_back(data);
}

}

}
