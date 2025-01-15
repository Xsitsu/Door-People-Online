#ifndef PACKET_PHYSICS_SETTINGS_HPP_INCLUDE
#define PACKET_PHYSICS_SETTINGS_HPP_INCLUDE

#include "network_dll_export.h"

#include <vector>

#include "packet.hpp"

namespace Network
{

namespace Packet
{

class DLL_EXPORT PhysicsSettings : public Packet::Base
{
public:
    PhysicsSettings(uint32_t conId, PacketAction action);
    virtual ~PhysicsSettings();
    virtual unsigned int GetPacketSize() const;

    

private:
    uint8_t num_bytes;
    std::vector<uint8_t> bytes;

};

}

}

#endif // PACKET_PHYSICS_SETTINGS_HPP_INCLUDE
