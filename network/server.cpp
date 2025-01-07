#include "server.hpp"

#include "network/packetall.hpp"

namespace Network
{

Server::Server() : conIdCounter(1), maxClients(0), connections(), connectionsPerAddr()
{
    this->log = Util::Logger::Instance()->GetLog("Server");
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
        this->DoHandlePacket(packet, sender);
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


ClientConnection* Server::GetConnectionFromAddress(const Address &address)
{
    for (auto it : this->connections)
    {
        ClientConnection *connection = it.second;
        if (connection->GetAddress() ==  address)
        {
            return connection;
        }
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
            this->connectionsPerAddr[addr] = numCons - 1;
        }

        this->connections.erase(conId);
    }
}


void Server::ClientConnectionAdded(ClientConnection *)
{

}

void Server::ClientConnectionRemoving(ClientConnection *)
{

}



bool Server::HandlePacket(Packet::Base *packet, const Address &)
{
    std::string packetFamilyName = PacketFamilyToString(packet->GetFamily());
    std::string packetActionName = PacketActionToString(packet->GetAction());
    std::string msg = "Got packet with I don't know what to do with: " + packetFamilyName + " " + packetActionName + "\n";

    this->log->LogMessage(msg, Util::LogLevel::Warn);

    return false;
}

bool Server::HandlePacket(Packet::Connect *packet, const Address &sender)
{
    if (packet->GetAction() == PacketAction::ACTION_REQUEST)
    {
        unsigned int addr = sender.GetAddress();
        uint32_t conNumber = this->NumConnectionsOnAddr(addr);
        if (conNumber >= 3)
        {
            Packet::Connect response(0, PacketAction::ACTION_DECLINE);
            this->SendPacket(&response, sender);

            std::string message = "Refused client connection with address: " + sender.ToString() + "\n";
            this->log->LogMessage(message, Util::LogLevel::Info);
        }
        else
        {
            ClientConnection *connection = this->GetConnectionFromAddress(sender);
            if (!connection)
            {
                uint32_t conId = this->conIdCounter++;
                while (conId == 0 || this->HasConnection(conId))
                {
                    conId = this->conIdCounter++;
                }

                this->AddConnection(conId, sender);

                Packet::Connect response(0, PacketAction::ACTION_ACCEPT);
                response.SetAssignedId(conId);
                this->SendPacket(&response, sender);

                std::string message = "Client connected with address: " + sender.ToString() + "\n";
                this->log->LogMessage(message, Util::LogLevel::Info);

                this->ClientConnectionAdded(this->GetConnection(conId));
            }
            else
            {
                Packet::Connect response(0, PacketAction::ACTION_ACCEPT);
                response.SetAssignedId(connection->GetConnectionId());
                this->SendPacket(&response, sender);

                std::string message = "Client reconnected with address: " + sender.ToString() + "\n";
                this->log->LogMessage(message, Util::LogLevel::Info);

                this->ClientConnectionAdded(connection);
            }
        }
        return true;
    }
    return false;
}

bool Server::HandlePacket(Packet::Disconnect *packet, const Address &sender)
{
    if (packet->GetAction() == PacketAction::ACTION_REQUEST)
    {
        uint32_t conId = packet->GetConnectionId();
        ClientConnection *connection = this->GetConnection(conId);
        if (connection)
        {
            if (connection->GetAddress() == sender)
            {
                this->ClientConnectionRemoving(connection);

                this->RemoveConnection(conId);
                Packet::Disconnect packet(0, PacketAction::ACTION_ACCEPT);
                this->SendPacket(&packet, sender);

                delete connection;

                std::string message = "Client disconnected with address: " + sender.ToString() + "\n";
                this->log->LogMessage(message, Util::LogLevel::Info);
            }
        }
        return true;
    }
    return false;
}

bool Server::HandlePacket(Packet::Terrain *, const Address &)
{
    return false;
}

bool Server::HandlePacket(Packet::Player *, const Address &)
{
    return false;
}

}
