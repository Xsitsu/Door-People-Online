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


Socket::Socket() : handle(0)
{}

Socket::~Socket()
{}

bool Socket::Open(unsigned short port)
{
	if (this->IsOpen())
	{
		return false;
	}

	this->handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (!this->IsOpen())
	{
		return false;
	}

	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	if (bind(this->handle, (const sockaddr*)&address, sizeof(sockaddr_in)) < 0)
    {
        this->Close();
        return false;
    }

#ifdef _WIN32
	DWORD nonBlocking = 1;
	if (ioctlsocket(handle, FIONBIO, &nonBlocking) != 0)
	{
		this->Close();
		return false;
	}

#else
	int nonBlocking = 1;
	if (fcntl(this->handle, F_SETFL, O_NONBLOCK, nonBlocking) == -1)
	{
		this->Close();
		return false;
	}

#endif

	return true;
}

void Socket::Close()
{
#ifdef _WIN32
    closesocket(this->handle);
    this->handle = 0;
#else
	close(this->handle);
	this->handle = 0
#endif
}

bool Socket::IsOpen() const
{
	return (this->handle > 0);
}

bool Socket::Send(const Address& destination, const void* data, int size)
{
	sockaddr_in addr = destination.ToSockaddr_in();

	int sent_bytes = sendto(this->handle, (const char*)data, size, 0, (sockaddr*)&addr, sizeof(sockaddr_in));
	return (sent_bytes == size);
}

int Socket::Receive(Address& sender, void* data, int size)
{
#ifdef _WIN32
	typedef int socklen_t;
#endif

	sockaddr_in from;
	socklen_t fromLength = sizeof(from);

	int bytes = recvfrom(this->handle, (char*)data, size, 0, (sockaddr*)&from, &fromLength);

	sender = Address((unsigned int)ntohl(from.sin_addr.s_addr), (unsigned short)ntohs(from.sin_port));

	return bytes;
}



}
