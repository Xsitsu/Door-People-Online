#ifndef SERVICE_HPP_INCLUDE
#define SERVICE_HPP_INCLUDE

#include "util_dll_export.h"

namespace Util
{

class ServiceProvider;

class DLL_EXPORT Service
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
