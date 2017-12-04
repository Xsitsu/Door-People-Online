#include "address.hpp"

#include <sstream>

namespace Network
{

Address::Address() : address(0), port(0)
{}

Address::Address(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port) : address(0), port(port)
{
	address = (a << 24) | (b << 16) | (c << 8) | d;
}

Address::Address(unsigned int address, unsigned short port) : address(address), port(port)
{}

unsigned int Address::GetAddress() const
{
	return this->address;
}

unsigned char Address::GetA() const
{
	unsigned int shifter = 255;
	return (this->address >> 24) & shifter;
}

unsigned char Address::GetB() const
{
	unsigned int shifter = 255;
	return (this->address >> 16) & shifter;
}

unsigned char Address::GetC() const
{
	unsigned int shifter = 255;
	return (this->address >> 8) & shifter;
}

unsigned char Address::GetD() const
{
	unsigned int shifter = 255;
	return this->address & shifter;
}

unsigned short Address::GetPort() const
{
	return this->port;
}

sockaddr_in Address::ToSockaddr_in() const
{
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(this->GetAddress());
	addr.sin_port = htons(this->GetPort());

	return addr;
}

std::string Address::ToString() const
{
    std::stringstream stream;

    stream << (int)this->GetA() << "." << (int)this->GetB() << "."
        << (int)this->GetC() << "." << (int)this->GetD() << ":"
        << (int)this->GetPort();

    return stream.str();
}

bool Address::operator==(const Address& rhs) const
{
    return (this->address == rhs.address) && (this->port == rhs.port);
}


}
