#include "serviceprovider.hpp"

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
    this->log = Util::Logger::Instance()->GetLog("ServiceProvider");
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
        this->log->LogMessage(msg, Util::LogLevel::Error);
        this->log->Write(stdout);
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
