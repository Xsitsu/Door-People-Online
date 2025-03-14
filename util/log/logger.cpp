#include "logger.hpp"

namespace Util
{

Logger* Logger::i_logger = nullptr;

Logger* Logger::Instance()
{
    if (!Logger::i_logger)
    {
        Logger::i_logger = new Logger();
    }
    return Logger::i_logger;
}

Logger::Logger()
{
    this->GetLog("logger_debug");
}

Logger::~Logger()
{
    for (auto it : this->logs)
    {
        Log *log = it.second;
        it.second = nullptr;
        delete log;
    }
}

Logger::Logger(const Logger&)
{

}

Logger& Logger::operator= (const Logger&)
{
    return *this;
}

bool Logger::HasLog(std::string log_name)
{
    auto it = this->logs.find(log_name);
    return (it != this->logs.end());
}

Log* Logger::GetLog(std::string log_name)
{
    if (!this->HasLog(log_name))
    {
        this->logs[log_name] = new Log(log_name, &(this->entries));
    }

    return this->logs[log_name];
}

void Logger::WriteAll()
{
    auto entries_clone(this->entries);
    this->entries.clear();

    for (auto entry : entries_clone)
    {
        this->WriteEntryToFile(entry);
    }
}

void Logger::WriteEntryToFile(const LogEntry &entry)
{
    std::string format = "[%s %s] %s";
    std::string level_str = LogLevelToString(entry.level);
    fprintf(
        entry.source_log->GetOutputFile(),
        format.c_str(),

        entry.source_log->GetLogName().c_str(),
        level_str.c_str(),
        entry.message.c_str()
    );
}


}
