#ifndef PACKETBUILDER_HPP_INCLUDE
#define PACKETBUILDER_HPP_INCLUDE

#include "Network_dll-export.h"

#include "packet.hpp"

namespace Network
{

class DLL_EXPORT PacketBuilder
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
