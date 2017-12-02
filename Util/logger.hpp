#ifndef LOGGER_HPP_INCLUDE
#define LOGGER_HPP_INCLUDE

#include "main.h"

#include <string>\

#ifdef _WIN32
class DLL_EXPORT Logger {
#else
class Logger {
#endif // _WIN32
public:
    Logger();
    ~Logger();

    void CreateLogChannel(std::string channelName);
    void EnableLogChannel(std::string channelName);
    void DisableLogChannel(std::string channelName);

    void Log(std::string channelName, std::string message, ...);
protected:

};

#endif // LOGGER_HPP_INCLUDE
