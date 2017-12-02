#include "socket.hpp"

namespace Network
{

bool InitializeSockets()
{
#ifdef _WIN32
	WSADATA WsaData;
	return WSAStartup(MAKEWORD(2, 2), &WsaData) == NO_ERROR;
#else
	return true;
#endif
}

void ShutdownSockets()
{
#ifdef _WIN32
	WSACleanup();
#endif
}


}
