#include "client.hpp"

#include "network/packet/packetall.hpp"

namespace Network
{

Client::Client() : serverAddress(), isConnected(false), connectionId(0)
{
    this->log = Util::Logger::Instance()->GetLog("Client");
    this->log->SetLogLevel(Util::LogLevel::Debug);
}

Client::~Client()
{
    if (this->socket.IsOpen())
    {
        this->socket.Close();
    }

    this->log = nullptr;
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
    this->log->LogMessage("Client::Connect()\n", Util::LogLevel::Debug);
    if (!this->IsConnected())
    {
        this->log->LogMessage("Sending connection request to server!\n", Util::LogLevel::Info);
        this->serverAddress = serverAddress;

        Packet::Connect packet(0, PacketAction::ACTION_REQUEST);
        this->SendPacket(&packet, serverAddress);
    }
}

bool Client::IsConnected() const
{
    return this->isConnected;
}

void Client::Disconnect()
{
    this->log->LogMessage("Client::Disconnect()\n", Util::LogLevel::Debug);
    if (this->isConnected)
    {
        this->log->LogMessage("Sending disconnect request to server\n", Util::LogLevel::Info);
        Packet::Disconnect packet(this->connectionId, PacketAction::ACTION_REQUEST);
        this->SendPacket(&packet, this->serverAddress);

        this->isConnected = false;
    }
}

void Client::Tick()
{
    Address sender;
    Packet::Base *packet = this->ReceivePacket(sender);
    while (packet != nullptr)
    {
        if (sender == this->serverAddress)
        {
            this->DoHandlePacket(packet, sender);
            packet = this->ReceivePacket(sender);
        }
    }
}

const Address& Client::GetServerAddress() const
{
    return this->serverAddress;
}

uint32_t Client::GetConnectionId() const
{
    return this->connectionId;
}

bool Client::HandlePacket(Packet::Base *packet, const Address &)
{
    std::string packetFamilyName = PacketFamilyToString(packet->GetFamily());
    std::string packetActionName = PacketActionToString(packet->GetAction());
    std::string msg = "Got packet with I don't know what to do with: " + packetFamilyName + " " + packetActionName + "\n";

    this->log->LogMessage(msg, Util::LogLevel::Warn);

    return false;
}

bool Client::HandlePacket(Packet::Connect *packet, const Address &)
{
    this->log->LogMessage("Client::HandlePacket(Packet::Connect)\n", Util::LogLevel::Debug);
    if (packet->GetAction() == Network::PacketAction::ACTION_ACCEPT)
    {
        this->connectionId = packet->GetAssignedId();
        this->isConnected = true;

        std::string msg = "Established connection with server\n";
        this->log->LogMessage(msg, Util::LogLevel::Info);
        return true;
    }
    else if (packet->GetAction() == Network::PacketAction::ACTION_DECLINE)
    {
        std::string msg = "Connection was refused from server\n";
        this->log->LogMessage(msg, Util::LogLevel::Info);
        return true;
    }
    return false;
}

bool Client::HandlePacket(Packet::Disconnect *, const Address &)
{
    return false;
}

bool Client::HandlePacket(Packet::Terrain *, const Address &)
{
    return false;
}

bool Client::HandlePacket(Packet::Player *, const Address &)
{
    return false;
}

}
