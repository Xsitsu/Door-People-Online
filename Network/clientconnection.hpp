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
    ClientConnection(Address address);
    ~ClientConnection();

    const Address& GetAddress() const;

protected:
    Address address;

};

}

#endif // CLIENTCONNECTION_HPP_INCLUDE
