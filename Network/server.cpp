#include "server.hpp"

#include "network/packetall.hpp"

namespace Network
{

Server::Server() : maxClients(0), connections()
{

}

Server::~Server()
{
    this->Shutdown();
}

bool Server::Init(unsigned short port, unsigned int maxClients)
{
    if (!this->socket.IsOpen())
    {
        this->socket.Open(port);
        if (this->socket.IsOpen())
        {
            this->maxClients = maxClients;
            return true;
        }
    }
    return false;
}

void Server::Tick()
{
    Address sender;
    Packet::Base *packet = this->ReceivePacket(sender);
    while (packet != nullptr)
    {
        if (packet->GetFamily() == PacketFamily::FAMILY_CONNECT)
        {
            Packet::Connect *packet = static_cast<Packet::Connect*>(packet);
            ClientConnection *connection = this->connections[sender.GetAddress()];
            if (connection)
            {

            }
        }

        delete packet;
        packet = this->ReceivePacket(sender);
    }
}

void Server::Shutdown()
{
    if (this->socket.IsOpen())
    {
        this->socket.Close();

        for (auto it : this->connections)
        {
            ClientConnection *connection = it.second;
            delete connection;
        }
        this->connections.clear();
        this->maxClients = 0;
    }
}

bool Server::IsRunning() const
{
    return this->socket.IsOpen();
}

}
