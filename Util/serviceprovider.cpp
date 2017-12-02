#include "serviceprovider.hpp"

#include "logger.hpp"

namespace Util
{

ServiceProvider::ServiceProvider() : services()
{
    this->Init();
}

ServiceProvider::~ServiceProvider()
{

}

void ServiceProvider::Init()
{

}

bool ServiceProvider::HasService(std::string serviceName) const
{
    auto it = this->services.find(serviceName);
    return (it != this->services.end());
}

void ServiceProvider::AddService(std::string serviceName, Service* service)
{
    if (!this->HasService(serviceName))
    {
        this->services[serviceName] = service;
    }
}

Service* ServiceProvider::GetService(std::string serviceName)
{
    if (this->HasService(serviceName))
    {
        return this->services[serviceName];
    }
    else
    {
        return nullptr;
    }
}

void ServiceProvider::RemoveService(std::string serviceName)
{
    Service *service = this->GetService(serviceName);
    if (service)
    {
        service->SetServiceProvider(nullptr);
        this->services.erase(serviceName);
    }
}

void ServiceProvider::DestroyService(std::string serviceName)
{
    Service *service = this->GetService(serviceName);
    if (service)
    {
        service->SetServiceProvider(nullptr);
        this->services.erase(serviceName);
        delete service;
    }
}

}
