#include "clientconnection.hpp"

namespace Network
{

ClientConnection::ClientConnection(uint32_t conId, Address address) : connectionId(conId),address(address)
{

}

ClientConnection::~ClientConnection()
{

}

uint32_t ClientConnection::GetConnectionId() const
{
    return this->connectionId;
}

const Address& ClientConnection::GetAddress() const
{
    return this->address;
}

}
