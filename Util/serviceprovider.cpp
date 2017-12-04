#include "serviceprovider.hpp"

#include "logger.hpp"

namespace Util
{

ServiceProvider::ServiceProvider() : services()
{

}

ServiceProvider::~ServiceProvider()
{

}

void ServiceProvider::Init()
{
    if (!Util::Logger::Instance()->HasLogChannel("service_provider"))
    {
        Util::Logger::Instance()->CreateLogChannel("service_provider", "SVP", stdout);
        Util::Logger::Instance()->EnableLogChannel("service_provider");
    }
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
        service->SetServiceProvider(this);
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
        std::string msg = "Tried to get invalid service: " + serviceName + "\n";
        Util::Logger::Instance()->Log("service_provider", msg);
        Util::Logger::Instance()->Flush();
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
