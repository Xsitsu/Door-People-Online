#ifndef CLIENTCONNECTION_HPP_INCLUDE
#define CLIENTCONNECTION_HPP_INCLUDE

#include "address.hpp"

namespace Network
{

class DLL_EXPORT ClientConnection
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
