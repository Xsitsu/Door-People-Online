#ifndef LOGCHANNEL_HPP_INCLUDE
#define LOGCHANNEL_HPP_INCLUDE

#include "main.h"

#include <string>
#include <list>
#include <mutex>

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

    void AddLogEntry(std::string message);
    void Flush();

protected:
    LogChannel(const LogChannel& other);
    LogChannel& operator=(const LogChannel& other);

    std::string logTag;
    FILE* fileDesc;
    bool enabled;

    std::list<std::string> logEntries;

    //std::mutex *entriesLock;
};

}
#endif // LOGCHANNEL_HPP_INCLUDE
