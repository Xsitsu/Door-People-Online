#include "service.hpp"

namespace Util
{
Service::Service() : provider(nullptr)
{

}

Service::~Service()
{

}


Service::Service(const Service&) : provider(nullptr)
{

}

Service& Service::operator=(const Service& other)
{
    if (this != &other)
    {

    }

    return *this;
}

void Service::SetServiceProvider(ServiceProvider *provider)
{
    if (this->provider)
    {
        this->onServiceProviderRemoving();
    }

    this->provider = provider;

    if (this->provider)
    {
        this->onServiceProviderRemoving();
    }
}

ServiceProvider* Service::GetServiceProvider() const
{
    return this->provider;
}

void Service::onServiceProviderAdded()
{

}

void Service::onServiceProviderRemoving()
{

}

}


