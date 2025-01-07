#include "log.hpp"

namespace Util
{

Log::Log(std::string name)
{
    this->name = name;
    this->level = LogLevel::Debug;
}

void Log::LogMessage(std::string message, LogLevel level)
{
    if (this->level >= level)
    {
        this->DoLogMessage(message, level);
    }
}

void Log::DoLogMessage(std::string message, LogLevel level)
{
    LogEntry entry;
    entry.message = message;
    entry.level = level;
    this->entries.push_back(entry);
}

void Log::Write(FILE* fp)
{
    std::list<LogEntry> entry_clone(this->entries);
    this->entries = std::list<LogEntry>();

    std::string format = "[%s %s] %s";
    std::string level_str = "info";
    for (auto entry : entry_clone)
    {
        fprintf(
            fp,
            format.c_str(),
            this->name.c_str(),
            level_str.c_str(),
            entry.message.c_str()
        );
    }
}

void Log::SetLogLevel(LogLevel level)
{
    this->level = level;
}



}