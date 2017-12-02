#ifndef SOCKET_HPP_INCLUDE
#define SOCKET_HPP_INCLUDE

#include "main.h"

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

#ifdef _WIN32
bool DLL_EXPORT InitializeSockets();
void DLL_EXPORT ShutdownSockets();
#else
bool InitializeSockets();
void ShutdownSockets();
#endif // _WIN32

#ifdef _WIN32
class DLL_EXPORT Socket
#else
class Socket
#endif // _WIN32
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
