#include "packetterrain.hpp"

namespace Network
{

namespace Packet
{

Terrain::Terrain(uint32_t conId, PacketAction action) : Packet::Base(conId, PacketFamily::FAMILY_TERRAIN, action), terrainData()
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
