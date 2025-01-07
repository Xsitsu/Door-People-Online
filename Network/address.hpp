#ifndef ADDRESS_HPP_INCLUDE
#define ADDRESS_HPP_INCLUDE

#include "network_dll_export.h"

#include <string>

#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#endif // _WIN32

namespace Network
{

class DLL_EXPORT Address
{
public:
	Address();
	Address(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port);
	Address(unsigned int address, unsigned short port);
	unsigned int GetAddress() const;
	unsigned char GetA() const;
	unsigned char GetB() const;
	unsigned char GetC() const;
	unsigned char GetD() const;
	unsigned short GetPort() const;
	std::string ToString() const;

	sockaddr_in ToSockaddr_in() const;

	bool operator==(const Address& rhs) const;

protected:
	unsigned int address;
	unsigned short port;

};

}
#endif // ADDRESS_HPP_INCLUDE
