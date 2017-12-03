#ifndef PACKETBUILDER_HPP_INCLUDE
#define PACKETBUILDER_HPP_INCLUDE

#include "main.h"

#include "packet.hpp"

namespace Network
{

#ifdef _WIN32
class DLL_EXPORT PacketBuilder
#else
class PacketBuilder
#endif // _WIN32
{
public:
    static void BuildPacket(Packet::Base *packet, void *data);

protected:
    PacketBuilder();
    ~PacketBuilder();

    static void PutFamily(void *&data, PacketFamily value);
    static void PutAction(void *&data, PacketAction value);
    static void Put32(void *&data, uint32_t value);
    static void Put16(void *&data, uint16_t value);
    static void Put8(void *&data, uint8_t value);
};

}
#endif // PACKETBUILDER_HPP_INCLUDE
