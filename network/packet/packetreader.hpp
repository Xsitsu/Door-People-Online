#ifndef PACKETREADER_HPP_INCLUDE
#define PACKETREADER_HPP_INCLUDE

#include "network_dll_export.h"

#include "packet.hpp"

namespace Network
{

class DLL_EXPORT PacketReader
{
public:
    static Packet::Base* ReadPacket(unsigned int packetSize, void *data);
    
    static PacketFamily ReadFamily(void *&data);
    static PacketAction ReadAction(void *&data);
    static uint32_t Read32(void *&data);
    static uint16_t Read16(void *&data);
    static uint8_t Read8(void *&data);

protected:
    PacketReader();
    ~PacketReader();

};

}
#endif // PACKETREADER_HPP_INCLUDE
