#ifndef PACKET_PHYSICS_SETTINGS_HPP_INCLUDE
#define PACKET_PHYSICS_SETTINGS_HPP_INCLUDE

#include "network_dll_export.h"

#include <vector>

#include "packet.hpp"

#include "gamecore/physicssettings.hpp"

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

    virtual PacketFamily GetFamily() const;

    virtual void Encode(void *&data) const;
    virtual void Decode(unsigned int packet_size, void *&data);
    
    void SetPhysicsSettings(const Game::PhysicsSettings &settings);
    Game::PhysicsSettings GetPhysicsSettings() const;

private:
    Game::PhysicsSettings settings;

};

}

}

#endif // PACKET_PHYSICS_SETTINGS_HPP_INCLUDE
