#ifndef LOG_HPP_INCLUDE
#define LOG_HPP_INCLUDE

#include "Util_dll-export.h"

#include <string>
#include <list>

namespace Util
{

enum class DLL_EXPORT LogLevel
{
    FATAL,
    ERROR,
    WARN,
    INFO,
    DEBUG,
};

struct LogEntry
{
    std::string message = "";
    LogLevel level = LogLevel::FATAL;
};

class DLL_EXPORT Log
{
public:
    Log(std::string name);

    void LogMessage(std::string message, LogLevel level);
    void Write(FILE* fp);
    void SetLogLevel(LogLevel level);

protected:
    void DoLogMessage(std::string message, LogLevel level);

private:
    std::string name;
    LogLevel level = LogLevel::FATAL;
    std::list<LogEntry> entries;
};

}

#endif // LOG_HPP_INCLUDE
