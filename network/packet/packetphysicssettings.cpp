#include "packetphysicssettings.hpp"

#include "packetbuilder.hpp"
#include "packetreader.hpp"

namespace Network
{

namespace Packet
{

PhysicsSettings::PhysicsSettings()
{

}

PhysicsSettings::~PhysicsSettings()
{

}

unsigned int PhysicsSettings::GetPacketSize() const
{
    return this->num_bytes + 1;
}

void PhysicsSettings::Encode(void *data)
{
    PacketBuilder::PutFamily(data, packet->GetFamily());
    PacketBuilder::PutAction(data, packet->GetAction());
}

void PhysicsSettings::Decode(void *data)
{

}

}

}