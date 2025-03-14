#include "log.hpp"

namespace Util
{

std::string LogLevelToString(LogLevel level)
{
    switch (level)
    {
    case LogLevel::Fatal:
        return "Fatal";
    case LogLevel::Error:
        return "Error";
    case LogLevel::Warn:
        return "Warn";
    case LogLevel::Info:
        return "Info";
    case LogLevel::Debug:
        return "Debug";
    default:
        return "INVALID_LOG_LEVEL";
    }
}

Log::Log(std::string name, std::list<LogEntry> *entries_ptr)
{
    this->fp = stdout;
    this->name = name;
    this->level = LogLevel::Debug;
    this->entries_ptr = entries_ptr;
}

Log::~Log()
{
    // Log is not responsible for new and delete
    this->entries_ptr = nullptr;
}

void Log::SetLogLevel(LogLevel level)
{
    this->level = level;
}

void Log::LogMessage(std::string message, LogLevel level)
{
    if (this->level >= level && this->entries_ptr != nullptr)
    {
        this->DoLogMessage(message, level);
    }
}

std::string Log::GetLogName() const
{
    return this->name;
}

FILE* Log::GetOutputFile() const
{
    return this->fp;
}

void Log::SetOutputFile(FILE* fp)
{
    this->fp = fp;
}


void Log::DoLogMessage(std::string message, LogLevel level)
{
    auto entry = this->CreateLogEntry(message, level);
    this->entries_ptr->push_back(entry);
}

LogEntry Log::CreateLogEntry(std::string message, LogLevel level)
{
    LogEntry entry;
    entry.source_log = this;
    entry.message = message;
    entry.level = level;
    return entry;
}



}