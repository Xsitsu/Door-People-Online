#ifndef SERVICEPROVIDER_HPP_INCLUDE
#define SERVICEPROVIDER_HPP_INCLUDE

#include "main.h"

#include <string>
#include <unordered_map>

#include "service.hpp"

namespace Util
{

#ifdef _WIN32
class DLL_EXPORT ServiceProvider
#else
class ServiceProvider
#endif // _WIN32
{
public:
    ServiceProvider();
    virtual ~ServiceProvider();
    virtual void Init();

    bool HasService(std::string serviceName) const;
    void AddService(std::string serviceName, Service* service);
    Service* GetService(std::string serviceName);
    void RemoveService(std::string serviceName);
    void DestroyService(std::string serviceName); // remove then delete

protected:
    std::unordered_map<std::string, Service*> services;
};

}

#endif // SERVICEPROVIDER_HPP_INCLUDE
