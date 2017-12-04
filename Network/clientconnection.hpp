#ifndef CLIENTCONNECTION_HPP_INCLUDE
#define CLIENTCONNECTION_HPP_INCLUDE

#include "main.h"

#include "address.hpp"

namespace Network
{

#ifdef _WIN32
class DLL_EXPORT ClientConnection
#else
class ClientConnection
#endif // _WIN32
{
public:
    ClientConnection(uint32_t conId, Address address);
    ~ClientConnection();

    uint32_t GetConnectionId() const;
    const Address& GetAddress() const;

protected:
    uint32_t connectionId;
    Address address;

};

}

#endif // CLIENTCONNECTION_HPP_INCLUDE
