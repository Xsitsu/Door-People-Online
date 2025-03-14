#ifndef LOGGER_HPP_INCLUDE
#define LOGGER_HPP_INCLUDE

#include "util_dll_export.h"

#include <string>
#include <unordered_map>
#include <list>

#include "service.hpp"

#include "log.hpp"

namespace Util
{

class DLL_EXPORT Logger
{
public:
    static Logger* Instance();

    bool HasLog(std::string log_name);
    Log* GetLog(std::string log_name);
    void WriteAll();

protected:
    Logger();
    ~Logger();
    Logger(const Logger&);
    Logger& operator= (const Logger&);

protected:
    void WriteEntryToFile(const LogEntry &entry);

protected:
    std::unordered_map<std::string, Log*> logs;
    std::list<LogEntry> entries;

    static Logger* i_logger;
};

}

#endif // LOGGER_HPP_INCLUDE
