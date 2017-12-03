#ifndef PACKETREADER_HPP_INCLUDE
#define PACKETREADER_HPP_INCLUDE

#include "main.h"

#include "packet.hpp"

namespace Network
{

#ifdef _WIN32
class DLL_EXPORT PacketReader
#else
class PacketReader
#endif // _WIN32
{
public:
    static Packet::Base* ReadPacket(unsigned int packetSize, void *data);

protected:
    PacketReader();
    ~PacketReader();

    static PacketFamily ReadFamily(void *&data);
    static PacketAction ReadAction(void *&data);
    static uint32_t Read32(void *&data);
    static uint16_t Read16(void *&data);
    static uint8_t Read8(void *&data);
};

}
#endif // PACKETREADER_HPP_INCLUDE
