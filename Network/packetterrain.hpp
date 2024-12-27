#ifndef PACKETTERRAIN_HPP_INCLUDE
#define PACKETTERRAIN_HPP_INCLUDE

#include "Network_dll-export.h"

#include <list>

#include "packet.hpp"

namespace Network
{

namespace Packet
{

class DLL_EXPORT Terrain : public Packet::Base
{
public:
    struct TerrainData
    {
        uint8_t type;
        uint32_t posX;
        uint32_t posY;
        uint32_t sizeX;
        uint32_t sizeY;
    };

    Terrain(uint32_t conId, PacketAction action);
    virtual ~Terrain();
    virtual unsigned int GetPacketSize() const;

    const std::list<TerrainData>& GetTerrainData() const;
    void AddTerrainData(TerrainData data);

protected:
    std::list<TerrainData> terrainData;

};

}

}

#endif // PACKETTERRAIN_HPP_INCLUDE
