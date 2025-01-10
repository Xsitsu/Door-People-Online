#ifndef PACKET_PHYSICS_SETTINGS_HPP_INCLUDE
#define PACKET_PHYSICS_SETTINGS_HPP_INCLUDE

#include "network_dll_export.h"

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

    const std::list<PlayerData>& GetPlayerData() const;
    void AddPlayerData(PlayerData data);

private:
    
};

}

}

#endif // PACKET_PHYSICS_SETTINGS_HPP_INCLUDE
