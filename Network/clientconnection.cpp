#include "clientconnection.hpp"

namespace Network
{

ClientConnection::ClientConnection(Address address) : address(address)
{

}

ClientConnection::~ClientConnection()
{

}

const Address& ClientConnection::GetAddress() const
{
    return this->address;
}

}
