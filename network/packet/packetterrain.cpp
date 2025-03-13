#include "packetterrain.hpp"

#include "packetbuilder.hpp"
#include "packetreader.hpp"

namespace Network
{

namespace Packet
{

Terrain::Terrain(uint32_t conId, PacketAction action) : Packet::Base(conId, action), terrainData()
{

}

Terrain::~Terrain()
{

}

unsigned int Terrain::GetPacketSize() const
{
    int dataSize = sizeof(uint8_t) + (sizeof(uint32_t) * 4);
    int numData = this->terrainData.size();
    return sizeof(uint8_t) + (dataSize * numData) + Packet::Base::GetPacketSize();
}

PacketFamily Terrain::GetFamily() const
{
    return PacketFamily::FAMILY_TERRAIN;
}

void Terrain::Encode(void *&data) const
{
    Packet::Base::Encode(data);

    const std::list<Packet::Terrain::TerrainData> &terrain_data = this->GetTerrainData();
    uint8_t terrain_size = terrain_data.size();

    PacketBuilder::Put8(data, terrain_size);
    for (Packet::Terrain::TerrainData t_data : terrain_data)
    {
        PacketBuilder::Put8(data, t_data.type);
        PacketBuilder::Put32(data, t_data.posX);
        PacketBuilder::Put32(data, t_data.posY);
        PacketBuilder::Put32(data, t_data.sizeX);
        PacketBuilder::Put32(data, t_data.sizeY);
    }
}

void Terrain::Decode(unsigned int packet_size, void *&data)
{
    Packet::Base::Decode(packet_size, data);

    uint8_t terrain_size = PacketReader::Read8(data);
    for (uint8_t i = 0; i < terrain_size; i++)
    {
        Packet::Terrain::TerrainData t_data;
        t_data.type = PacketReader::Read8(data);
        t_data.posX = PacketReader::Read32(data);
        t_data.posY = PacketReader::Read32(data);
        t_data.sizeX = PacketReader::Read32(data);
        t_data.sizeY = PacketReader::Read32(data);
        this->AddTerrainData(t_data);
    }
}

const std::list<Terrain::TerrainData>& Terrain::GetTerrainData() const
{
    return this->terrainData;
}

void Terrain::AddTerrainData(TerrainData data)
{
    this->terrainData.push_back(data);
}

}

}
