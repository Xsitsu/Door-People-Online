#ifndef SERVICE_HPP_INCLUDE
#define SERVICE_HPP_INCLUDE

#include "main.h"

namespace Util
{

class ServiceProvider;

#ifdef _WIN32
class DLL_EXPORT Service
#else
class Service
#endif // _WIN32
{
public:
    Service();
    virtual ~Service();
    Service(const Service&);
    Service& operator=(const Service& other);

    void SetServiceProvider(ServiceProvider *provider);
    ServiceProvider* GetServiceProvider() const;

protected:
    virtual void onServiceProviderAdded();
    virtual void onServiceProviderRemoving();

    ServiceProvider* provider;

};

}

#endif // SERVICE_HPP_INCLUDE
