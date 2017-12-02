#ifndef LOGCHANNEL_HPP_INCLUDE
#define LOGCHANNEL_HPP_INCLUDE

#include "main.h"

#include <string>

namespace Util
{

#ifdef _WIN32
class DLL_EXPORT LogChannel
#else
class LogChannel
#endif // _WIN32
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
