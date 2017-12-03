#ifndef SERVER_HPP_INCLUDE
#define SERVER_HPP_INCLUDE

#include "main.h"

#include <unordered_map>

#include "networkpeer.hpp"
#include "clientconnection.hpp"

namespace Network
{

#ifdef _WIN32
class DLL_EXPORT Server : public NetworkPeer
#else
class Server : public NetworkPeer
#endif // _WIN32
{
public:
    Server();
    virtual ~Server();

    bool Init(unsigned short port, unsigned int maxClients);
    void Tick();
    void Shutdown();
    bool IsRunning() const;

protected:
    unsigned int maxClients;
    std::unordered_map<unsigned int, ClientConnection*> connections;
};

}

#endif // SERVER_HPP_INCLUDE
