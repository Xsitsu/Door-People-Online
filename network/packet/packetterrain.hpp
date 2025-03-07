#ifndef PACKETTERRAIN_HPP_INCLUDE
#define PACKETTERRAIN_HPP_INCLUDE

#include "network_dll_export.h"

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

    virtual PacketFamily GetFamily() const;

    virtual void Encode(void *data) const;
    virtual void Decode(unsigned int packet_size, void *data);
    
    const std::list<TerrainData>& GetTerrainData() const;
    void AddTerrainData(TerrainData data);

protected:
    std::list<TerrainData> terrainData;

};

}

}

#endif // PACKETTERRAIN_HPP_INCLUDE
