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

class DLL_EXPORT Log;

struct LogEntry
{
    Log *source_log;
    std::string message = "";
    LogLevel level = LogLevel::Fatal;
};

std::string LogLevelToString(LogLevel level);

class DLL_EXPORT Log
{
public:
    Log(std::string name, std::list<LogEntry> *entries_ptr);
    ~Log();

    void SetLogLevel(LogLevel level);
    void LogMessage(std::string message, LogLevel level);

    std::string GetLogName() const;
    FILE* GetOutputFile() const;
    void SetOutputFile(FILE*);

protected:
    void DoLogMessage(std::string message, LogLevel level);
    LogEntry CreateLogEntry(std::string message, LogLevel level);

private:
    std::string name;
    LogLevel level;
    FILE *fp;

    std::list<LogEntry> *entries_ptr;
};

}

#endif // LOG_HPP_INCLUDE
