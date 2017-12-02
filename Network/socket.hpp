#ifndef SOCKET_HPP_INCLUDE
#define SOCKET_HPP_INCLUDE

#include "main.h"

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

protected:

};

}
#endif // SOCKET_HPP_INCLUDE
