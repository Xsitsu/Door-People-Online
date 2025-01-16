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
    auto base_size = Packet::Base::GetPacketSize();
    auto size_8 = this->bytes.size() + 1;
    return (sizeof(uint8_t) * size_8) + base_size;
}

void PhysicsSettings::Encode(void *&data)
{
    Packet::Base::Encode(data);
    
}

void PhysicsSettings::Decode(void *data)
{

}

}

}