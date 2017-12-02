#ifndef LOGGER_HPP_INCLUDE
#define LOGGER_HPP_INCLUDE

#include "main.h"

#include <string>
#include <unordered_map>

#include "logchannel.hpp"

namespace Util
{

#ifdef _WIN32
class DLL_EXPORT Logger
#else
class Logger
#endif // _WIN32
{
public:
    Logger();
    ~Logger();

    bool HasLogChannel(std::string channelName) const;
    void CreateLogChannel(std::string channelName, std::string tag, FILE* fileDesc);
    void EnableLogChannel(std::string channelName);
    void DisableLogChannel(std::string channelName);
    bool IsLogChannelEnabled(std::string channelName) const;

    void Log(std::string channelName, std::string message);
protected:
    std::unordered_map<std::string, LogChannel*> logChannels;

};

}

#endif // LOGGER_HPP_INCLUDE
