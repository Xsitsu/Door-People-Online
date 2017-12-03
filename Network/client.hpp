#ifndef CLIENT_HPP_INCLUDE
#define CLIENT_HPP_INCLUDE

#include "main.h"

#include "networkpeer.hpp"

namespace Network
{

#ifdef _WIN32
class DLL_EXPORT Client : public NetworkPeer
#else
class Client : public NetworkPeer
#endif // _WIN32
{
public:
    Client();
    virtual ~Client();

    bool Init(unsigned short port);
    void Connect(const Address &serverAddress);
    bool IsConnected() const;

    const Address& GetServerAddress() const;

protected:
    Address serverAddress;
    bool isConnected;
};

}


#endif // CLIENT_HPP_INCLUDE
