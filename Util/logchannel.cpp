#include "logchannel.hpp"

#include <stdio.h>

namespace Util
{

LogChannel::LogChannel(std::string logTag, FILE* fileDesc) : logTag(logTag), fileDesc(fileDesc), enabled(false)
{

}

LogChannel::~LogChannel()
{
    fclose(this->fileDesc);
}

LogChannel::LogChannel(const LogChannel& other) : logTag(other.logTag), fileDesc(other.fileDesc), enabled(other.enabled)
{

}

LogChannel& LogChannel::operator=(const LogChannel& other)
{
    if (this != &other)
    {

    }

    return *this;
}

bool LogChannel::IsEnabled() const
{
    return this->enabled;
}

void LogChannel::Enable()
{
    this->enabled = true;
}

void LogChannel::Disable()
{
    this->enabled = false;
}

std::string LogChannel::GetLogTag() const
{
    return this->logTag;
}

FILE* LogChannel::GetFileDesc() const
{
    return this->fileDesc;
}

}
