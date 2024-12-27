#ifndef SOCKET_HPP_INCLUDE
#define SOCKET_HPP_INCLUDE

#include "Network_dll-export.h"

#include "address.hpp"

#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#endif // _WIN32

namespace Network
{

bool DLL_EXPORT InitializeSockets();
void DLL_EXPORT ShutdownSockets();

class DLL_EXPORT Socket
{
public:
	Socket();
	~Socket();
	bool Open(unsigned short port);
	void Close();
	bool IsOpen() const;
	bool Send(const Address& destination, const void* data, int size);
	int Receive(Address& sender, void* data, int size);

protected:
	int handle;

};

}
#endif // SOCKET_HPP_INCLUDE
