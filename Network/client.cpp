#include "client.hpp"

#include "network/packetall.hpp"

namespace Network
{

Client::Client() : serverAddress(), isConnected(false)
{

}

Client::~Client()
{
    if (this->socket.IsOpen())
    {
        this->socket.Close();
    }
}

bool Client::Init(unsigned short port)
{
    if (!this->socket.IsOpen())
    {
        this->socket.Open(port);
        if (this->socket.IsOpen())
        {
            return true;
        }
    }
    return false;
}

void Client::Connect(const Address &serverAddress)
{
    if (!this->IsConnected())
    {
        this->serverAddress = serverAddress;

        Packet::Connect packet(0, PacketAction::ACTION_REQUEST);
        this->SendPacket(&packet, serverAddress);

        this->isConnected = true;
    }
}

bool Client::IsConnected() const
{
    return this->isConnected;
}

const Address& Client::GetServerAddress() const
{
    return this->serverAddress;
}

}
