#include "packetplayer.hpp"

#include "packetbuilder.hpp"
#include "packetreader.hpp"

#include <sstream>

namespace Network
{

namespace Packet
{

Player::Player(uint32_t conId, PacketAction action) : Packet::Base(conId, action), playerData()
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

PacketFamily Player::GetFamily() const
{
    return PacketFamily::FAMILY_PLAYER;
}

void Player::Encode(void *data) const
{
    Packet::Base::Encode(data);

    const std::list<Packet::Player::PlayerData> &player_data = this->GetPlayerData();
    uint8_t num_players = player_data.size();

    PacketBuilder::Put8(data, num_players);
    for (Packet::Player::PlayerData p_data : player_data)
    {
        PacketBuilder::Put32(data, p_data.playerId);
        PacketBuilder::Put8(data, p_data.direction);
        PacketBuilder::Put32(data, p_data.posX);
        PacketBuilder::Put32(data, p_data.posY);
        PacketBuilder::Put32(data, p_data.velX);
        PacketBuilder::Put32(data, p_data.velY);
    }
}

void Player::Decode(unsigned int packet_size, void *data)
{
    Packet::Base::Decode(packet_size, data);

    uint8_t num_players = PacketReader::Read8(data);
    for (uint8_t i = 0; i < num_players; i++)
    {
        Packet::Player::PlayerData p_data;
        p_data.playerId = PacketReader::Read32(data);
        p_data.direction = PacketReader::Read8(data);
        p_data.posX = PacketReader::Read32(data);
        p_data.posY = PacketReader::Read32(data);
        p_data.velX = PacketReader::Read32(data);
        p_data.velY = PacketReader::Read32(data);
        this->AddPlayerData(p_data);
    }
}

const std::list<Player::PlayerData>& Player::GetPlayerData() const
{
    return this->playerData;
}

void Player::AddPlayerData(PlayerData data)
{
    this->playerData.push_back(data);
}

std::string Player::ToStrBody() const
{
    int num_players = this->GetPlayerData().size();

    std::stringstream ss;
    ss << Packet::Base::ToStrBody();
    ss << ", NumPlayers=";
    ss << num_players;
    return ss.str();
}

}

}
