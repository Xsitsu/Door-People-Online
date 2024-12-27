#include "networkpeer.hpp"

#include <cstring>
#include <vector>

#include "packetreader.hpp"
#include "packetbuilder.hpp"

#define MAX_PACKET_SIZE 1024

namespace Network {
	NetworkPeer::NetworkPeer() {
	}

	NetworkPeer::~NetworkPeer() {
	}

	Packet::Base *NetworkPeer::ReceivePacket(Address &sender) {
		char buffer[MAX_PACKET_SIZE];
		Packet::Base *packet = nullptr;

		int bytesRead = 0;
		bool reading = true;
		while (reading) {
			bytesRead = this->socket.Receive(sender, buffer, sizeof(buffer));
			if (bytesRead <= 0) {
				reading = false;
			} else if (bytesRead <= MAX_PACKET_SIZE) {
				packet = PacketReader::ReadPacket(bytesRead, buffer);
				reading = false;
			}
		}

		return packet;
	}

	void NetworkPeer::SendPacket(Packet::Base *packet, const Address &destination) {
		unsigned int dataSize = packet->GetPacketSize();
		std::vector<char> charbuffer(dataSize);

		char *buffer = charbuffer.data();
		memset(buffer, 0, sizeof(buffer));
		PacketBuilder::BuildPacket(packet, buffer);
		this->socket.Send(destination, buffer, dataSize);
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
		} else {
			wasHandled = this->HandlePacket(packet, sender);
		}
		delete packet;

		return wasHandled;
	}
}
