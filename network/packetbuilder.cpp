#include "packetbuilder.hpp"

#include "Network/packetall.hpp"

namespace Network
{

PacketBuilder::PacketBuilder()
{

}

PacketBuilder::~PacketBuilder()
{

}

void PacketBuilder::BuildPacket(Packet::Base *packet, void *data)
{
    PacketFamily family = packet->GetFamily();
    PacketAction action = packet->GetAction();

    PacketBuilder::Put32(data, packet->GetConnectionId());
    PacketBuilder::PutFamily(data, family);
    PacketBuilder::PutAction(data, action);

    if (family == PacketFamily::FAMILY_CONNECT)
    {
        Packet::Connect *pkt = static_cast<Packet::Connect*>(packet);
        PacketBuilder::Put32(data, pkt->GetAssignedId());
    }
    else if (family == PacketFamily::FAMILY_DISCONNECT)
    {
        //Packet::Disconnect *pkt = static_cast<Packet::Disconnect*>(packet);
        // nothing else required
    }
    else if (family == PacketFamily::FAMILY_TERRAIN)
    {
        Packet::Terrain *pkt = static_cast<Packet::Terrain*>(packet);
        const std::list<Packet::Terrain::TerrainData> &terrainData = pkt->GetTerrainData();
        uint8_t terrainSize = terrainData.size();

        PacketBuilder::Put8(data, terrainSize);
        for (Packet::Terrain::TerrainData tData : terrainData)
        {
            PacketBuilder::Put8(data, tData.type);
            PacketBuilder::Put32(data, tData.posX);
            PacketBuilder::Put32(data, tData.posY);
            PacketBuilder::Put32(data, tData.sizeX);
            PacketBuilder::Put32(data, tData.sizeY);
        }
    }
    else if (family == PacketFamily::FAMILY_PLAYER)
    {
        Packet::Player *pkt = static_cast<Packet::Player*>(packet);
        const std::list<Packet::Player::PlayerData> &playerData = pkt->GetPlayerData();
        uint8_t numPlayers = playerData.size();

        PacketBuilder::Put8(data, numPlayers);
        for (Packet::Player::PlayerData pData : playerData)
        {
            PacketBuilder::Put32(data, pData.playerId);
            PacketBuilder::Put8(data, pData.direction);
            PacketBuilder::Put32(data, pData.posX);
            PacketBuilder::Put32(data, pData.posY);
            PacketBuilder::Put32(data, pData.velX);
            PacketBuilder::Put32(data, pData.velY);
        }
    }
}

void PacketBuilder::PacketBuilder::PutFamily(void *&data, PacketFamily value)
{
    PacketFamily *d = static_cast<PacketFamily*>(data);
    *d = value;
    d++;
    data = d;
}

void PacketBuilder::PutAction(void *&data, PacketAction value)
{
    PacketAction *d = static_cast<PacketAction*>(data);
    *d = value;
    d++;
    data = d;
}

void PacketBuilder::Put32(void *&data, uint32_t value)
{
    uint32_t *d = static_cast<uint32_t*>(data);
    *d = htonl(value);
    d++;
    data = d;
}

void PacketBuilder::Put16(void *&data, uint16_t value)
{
    uint16_t *d = static_cast<uint16_t*>(data);
    *d = htons(value);
    d++;
    data = d;
}

void PacketBuilder::Put8(void *&data, uint8_t value)
{
    uint8_t *d = static_cast<uint8_t*>(data);
    *d = value;
    d++;
    data = d;
}

}
