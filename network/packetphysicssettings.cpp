#include "packetphysicssettings.hpp"

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

}

}