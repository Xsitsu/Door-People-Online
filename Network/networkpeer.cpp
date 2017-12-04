#include "networkpeer.hpp"

#include "packetreader.hpp"
#include "packetbuilder.hpp"

namespace Network
{
NetworkPeer::NetworkPeer() : maxPacketSize(1024)
{

}

NetworkPeer::~NetworkPeer()
{

}

Packet::Base* NetworkPeer::ReceivePacket(Address &sender)
{
    char buffer[this->maxPacketSize];
    Packet::Base *packet = nullptr;

    int bytesRead = 0;
    bool reading = true;
    while (reading)
    {
        bytesRead = this->socket.Receive(sender, buffer, sizeof(buffer));
        if (bytesRead <= 0)
        {
            reading = false;
        }
        else if (bytesRead <= maxPacketSize)
        {
            packet = PacketReader::ReadPacket(bytesRead, buffer);
            reading = false;
        }
    }

    return packet;
}

void NetworkPeer::SendPacket(Packet::Base* packet, const Address &destination)
{
    unsigned int dataSize = packet->GetPacketSize();
    char buffer[dataSize];
    memset(buffer, 0, sizeof(buffer));
    PacketBuilder::BuildPacket(packet, buffer);
    this->socket.Send(destination, buffer, dataSize);
}

void NetworkPeer::SetMaxPacketSize(int buffSize)
{
    this->maxPacketSize = buffSize;
}

}
