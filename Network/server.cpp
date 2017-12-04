#include "server.hpp"

#include "network/packetall.hpp"

#include "util/logger.hpp"

namespace Network
{

Server::Server() : conIdCounter(0), maxClients(0), connections(), connectionsPerAddr()
{
    if (!Util::Logger::Instance()->HasLogChannel("server"))
    {
        Util::Logger::Instance()->CreateLogChannel("server", "SRVR", stdout);
        Util::Logger::Instance()->EnableLogChannel("server");
    }
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
            unsigned int addr = sender.GetAddress();
            uint32_t conNumber = this->NumConnectionsOnAddr(addr);
            if (conNumber >= 3)
            {
                Packet::Connect response(0, PacketAction::ACTION_DECLINE);
                this->SendPacket(&response, sender);
            }
            else
            {
                uint32_t conId = this->conIdCounter++;
                while (this->HasConnection(conId))
                {
                    conId = this->conIdCounter++;
                }

                this->AddConnection(conId, sender);
                ClientConnection *connection = this->GetConnection(conId);

                Packet::Connect response(0, PacketAction::ACTION_ACCEPT);
                response.SetAssignedId(conId);
                this->SendPacket(&response, sender);

                Util::Logger::Instance()->Log("server", "Accepted client connection!\n");
            }
        }
        else if (packet->GetFamily() == PacketFamily::FAMILY_DISCONNECT)
        {

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

unsigned int Server::NumConnectionsOnAddr(uint32_t addr) const
{
    auto srch = this->connectionsPerAddr.find(addr);
    if (srch != this->connectionsPerAddr.end())
    {
        return srch->second;
    }
    return 0;
}

bool Server::HasConnection(uint32_t conId) const
{
    auto srch = this->connections.find(conId);
    if (srch != this->connections.end())
    {
        return true;
    }
    return false;
}

ClientConnection* Server::GetConnection(uint32_t conId)
{
    auto srch = this->connections.find(conId);
    if (srch != this->connections.end())
    {
        return srch->second;
    }
    return nullptr;
}

void Server::AddConnection(uint32_t conId, const Address &address)
{
    if (!this->GetConnection(conId))
    {
        ClientConnection *connection = new ClientConnection(conId, address);
        this->connections[conId] = connection;

        unsigned int addr = address.GetAddress();
        uint32_t numCons = this->NumConnectionsOnAddr(addr);
        this->connectionsPerAddr[addr] = numCons + 1;
    }
}

void Server::RemoveConnection(uint32_t conId)
{
    ClientConnection *connection = this->GetConnection(conId);
    if (connection)
    {
        unsigned int addr = connection->GetAddress().GetAddress();
        uint32_t numCons = this->NumConnectionsOnAddr(addr);
        if (numCons > 0)
        {
            this->connectionsPerAddr[addr] = numCons--;
        }

        this->connections.erase(conId);
    }
}


}
