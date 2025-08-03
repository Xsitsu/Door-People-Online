#include "networkpeer.hpp"

#include <cstring>
#include <vector>
#include <sstream>

#include "packet/packetreader.hpp"
#include "packet/packetbuilder.hpp"

#include "util/log/logger.hpp"


namespace Network {
	NetworkPeer::NetworkPeer()
	{}

	NetworkPeer::~NetworkPeer()
	{}

	Packet::Base *NetworkPeer::ReceivePacket(Address &sender)
	{
		Packet::Base *packet = nullptr;

		int bytesRead = 0;
		bool reading = true;
		while (reading)
		{
			bytesRead = this->socket.Receive(sender, this->buffer, sizeof(buffer));
			if (bytesRead <= 0)
			{
				reading = false;
			}
			else if (bytesRead <= MAX_PACKET_SIZE)
			{
				Util::Logger::Instance()->GetLog("Network")->LogMessage("Reading packet\n", Util::LogLevel::Debug);
				packet = PacketReader::ReadPacket(bytesRead, buffer);
				reading = false;

				std::stringstream ss;
				ss << "Got Packet: " << packet->ToStr() << std::endl;
				Util::Logger::Instance()->GetLog("Network")->LogMessage(ss.str(), Util::LogLevel::Debug);
			}
		}

		return packet;
	}

	void NetworkPeer::SendPacket(Packet::Base *packet, const Address &destination) {
		unsigned int dataSize = packet->GetPacketSize();
		std::vector<char> charbuffer(dataSize, 0);

		char *buffer = charbuffer.data();
		PacketBuilder::BuildPacket(packet, buffer);
		this->socket.Send(destination, buffer, dataSize);

		std::stringstream ss;
		ss << "Sent Packet: " << packet->ToStr() << std::endl;
		Util::Logger::Instance()->GetLog("Network")->LogMessage(ss.str(), Util::LogLevel::Debug);
	}

	bool NetworkPeer::DoHandlePacket(Packet::Base *packet, const Address &sender) {
		bool wasHandled = false;
		if (packet->GetFamily() == PacketFamily::FAMILY_CONNECT) {
			wasHandled = this->HandlePacket(static_cast<Packet::Connect *>(packet), sender);
		} else if (packet->GetFamily() == PacketFamily::FAMILY_DISCONNECT) {
			wasHandled = this->HandlePacket(static_cast<Packet::Disconnect *>(packet), sender);
		} else if (packet->GetFamily() == PacketFamily::FAMILY_TERRAIN) {
			wasHandled = this->HandlePacket(static_cast<Packet::Terrain *>(packet), sender);
		} else if (packet->GetFamily() == PacketFamily::FAMILY_PLAYER) {
			wasHandled = this->HandlePacket(static_cast<Packet::Player *>(packet), sender);
		} else if (packet->GetFamily() == PacketFamily::FAMILY_PHYSICS_SETTINGS) {
			wasHandled = this->HandlePacket(static_cast<Packet::PhysicsSettings *>(packet), sender);
		} else {
			wasHandled = this->HandlePacket(packet, sender);
		}
		delete packet;

		return wasHandled;
	}
}
