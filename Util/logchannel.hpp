#ifndef LOGCHANNEL_HPP_INCLUDE
#define LOGCHANNEL_HPP_INCLUDE

#include "Util_dll-export.h"

#include <string>

namespace Util
{

class DLL_EXPORT LogChannel
{
public:
    LogChannel(std::string logTag, FILE* fileDesc);
    ~LogChannel();

    bool IsEnabled() const;
    void Enable();
    void Disable();

    std::string GetLogTag() const;
    FILE* GetFileDesc() const;

protected:
    LogChannel(const LogChannel& other);
    LogChannel& operator=(const LogChannel& other);

    std::string logTag;
    FILE* fileDesc;
    bool enabled;
};

}
#endif // LOGCHANNEL_HPP_INCLUDE
