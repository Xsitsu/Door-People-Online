#ifndef LOGGER_HPP_INCLUDE
#define LOGGER_HPP_INCLUDE

#include "main.h"

#include <string>
#include <unordered_map>
#include <list>

#include "service.hpp"

#include "logchannel.hpp"

namespace Util
{

struct LogEntry
{
    LogChannel *channel = nullptr;
    std::string message = "";
};

#ifdef _WIN32
class DLL_EXPORT Logger
#else
class Logger
#endif // _WIN32
{
public:
    static Logger* Instance();

    bool HasLogChannel(std::string channelName) const;
    void CreateLogChannel(std::string channelName, std::string tag, FILE* fileDesc);
    void EnableLogChannel(std::string channelName);
    void DisableLogChannel(std::string channelName);
    bool IsLogChannelEnabled(std::string channelName) const;

    void Log(std::string channelName, std::string message);
    void Flush();

protected:
    Logger();
    ~Logger();
    Logger(const Logger&);
    Logger& operator= (const Logger&);

    std::unordered_map<std::string, LogChannel*> logChannels;
    std::list<LogEntry> logEntries;

    static Logger* i_logger;
};

}

#endif // LOGGER_HPP_INCLUDE
