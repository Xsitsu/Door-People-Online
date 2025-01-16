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

    void Encode(void *&data);
    void Decode(void *&data);

private:
    std::vector<uint8_t> bytes;

};

}

}

#endif // PACKET_PHYSICS_SETTINGS_HPP_INCLUDE
