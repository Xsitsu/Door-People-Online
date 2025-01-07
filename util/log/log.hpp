#ifndef LOG_HPP_INCLUDE
#define LOG_HPP_INCLUDE

#include "util_dll_export.h"

#include <string>
#include <list>

namespace Util
{

enum class DLL_EXPORT LogLevel
{
    Fatal,
    Error,
    Warn,
    Info,
    Debug,
};

struct LogEntry
{
    std::string message = "";
    LogLevel level = LogLevel::Fatal;
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
    LogLevel level;
    std::list<LogEntry> entries;
};

}

#endif // LOG_HPP_INCLUDE
