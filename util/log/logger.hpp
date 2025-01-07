#ifndef LOGGER_HPP_INCLUDE
#define LOGGER_HPP_INCLUDE

#include "Util_dll-export.h"

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
    void WriteAll(FILE *fp);

protected:
    Logger();
    ~Logger();
    Logger(const Logger&);
    Logger& operator= (const Logger&);

    std::unordered_map<std::string, Log*> logs;

    static Logger* i_logger;
};

}

#endif // LOGGER_HPP_INCLUDE
