#include "client.hpp"

#include "Util/logger.hpp"

#include "Network/packetall.hpp"

static const char *logChannelName = "client";
static const char *logChannelTag = "CLNT";

namespace Network
{

Client::Client() : serverAddress(), isConnected(false), connectionId(0)
{
    if (!Util::Logger::Instance()->HasLogChannel(logChannelName))
    {
        Util::Logger::Instance()->CreateLogChannel(logChannelName, logChannelTag, stdout);
        Util::Logger::Instance()->EnableLogChannel(logChannelName);
    }
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
    }
}

bool Client::IsConnected() const
{
    return this->isConnected;
}

void Client::Disconnect()
{
    if (this->isConnected)
    {
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
    Util::Logger::Instance()->Log(logChannelName, msg);

    return false;
}

bool Client::HandlePacket(Packet::Connect *packet, const Address &)
{
    if (packet->GetAction() == Network::PacketAction::ACTION_ACCEPT)
    {
        this->connectionId = packet->GetAssignedId();
        this->isConnected = true;

        std::string msg = "Established connection with server\n";
        Util::Logger::Instance()->Log(logChannelName, msg);
        return true;
    }
    else if (packet->GetAction() == Network::PacketAction::ACTION_DECLINE)
    {
        std::string msg = "Connection was refused from server\n";
        Util::Logger::Instance()->Log(logChannelName, msg);
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
