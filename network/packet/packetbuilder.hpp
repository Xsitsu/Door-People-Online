#ifndef PACKETBUILDER_HPP_INCLUDE
#define PACKETBUILDER_HPP_INCLUDE

#include "network_dll_export.h"

#include "packet.hpp"

namespace Network
{

class DLL_EXPORT PacketBuilder
{
public:
    static void BuildPacket(Packet::Base *packet, void *data);

    static const void PutFamily(void *&data, PacketFamily value);
    static const void PutAction(void *&data, PacketAction value);
    static const void Put32(void *&data, uint32_t value);
    static const void Put16(void *&data, uint16_t value);
    static const void Put8(void *&data, uint8_t value);

protected:
    PacketBuilder();
    ~PacketBuilder();
};

}
#endif // PACKETBUILDER_HPP_INCLUDE
