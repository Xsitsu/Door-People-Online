#ifndef TIMER_HPP_INCLUDE
#define TIMER_HPP_INCLUDE

#include <chrono>

#include "util_dll_export.h"

namespace Util
{

class DLL_EXPORT Timer
{
public:
    Timer();
    ~Timer();

    void Start();
    void Stop();
    void Reset();

    double GetSeconds() const;
    double GetMiliSeconds() const;

protected:
    uint64_t time_count;
    bool is_running;

    inline uint64_t GetNow() const;
};

}

#endif // TIMER_HPP_INCLUDE
