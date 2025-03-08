#include "packetphysicssettings.hpp"

#include "packetbuilder.hpp"
#include "packetreader.hpp"

namespace Network
{

namespace Packet
{

PhysicsSettings::PhysicsSettings(uint32_t conId, PacketAction action) : Packet::Base(conId, action)
{

}

PhysicsSettings::~PhysicsSettings()
{

}

unsigned int PhysicsSettings::GetPacketSize() const
{
    auto base_size = Packet::Base::GetPacketSize();
    return base_size + (sizeof(uint32_t) * 3);
}

PacketFamily PhysicsSettings::GetFamily() const
{
    return PacketFamily::FAMILY_PHYSICS_SETTINGS;
}

void PhysicsSettings::Encode(void *&data) const
{
    Packet::Base::Encode(data);
    
    PacketBuilder::Put32(data, (uint32_t)(this->settings.GetGravity()));
    PacketBuilder::Put32(data, (uint32_t)(this->settings.GetDefaultWalkspeed()));
    PacketBuilder::Put32(data, (uint32_t)(this->settings.GetDefaultJumpPower()));
}

void PhysicsSettings::Decode(unsigned int packet_size, void *&data)
{
    Packet::Base::Decode(packet_size, data);

    this->settings.gravity = (int)(PacketReader::Read32(data));
    this->settings.default_walkspeed = (int)(PacketReader::Read32(data));
    this->settings.default_jump_power = (int)(PacketReader::Read32(data));
}

void PhysicsSettings::SetPhysicsSettings(Game::PhysicsSettings settings)
{
    this->settings = settings;
}

Game::PhysicsSettings PhysicsSettings::GetPhysicsSettings() const
{
    return this->settings;
}

}

}