#include "logchannel.hpp"

#include <stdio.h>

namespace Util
{

LogChannel::LogChannel(std::string logTag, FILE* fileDesc) : logTag(logTag), fileDesc(fileDesc), enabled(false), logEntries()//, entriesLock(nullptr)
{
    //this->entriesLock = new std::mutex;
}

LogChannel::~LogChannel()
{

}

LogChannel::LogChannel(const LogChannel& other) : logTag(other.logTag), fileDesc(other.fileDesc), enabled(other.enabled), logEntries(other.logEntries)//, entriesLock(nullptr)
{
    //this->entriesLock = new std::mutex();
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

void LogChannel::AddLogEntry(std::string message)
{
    //this->entriesLock->lock();
    this->logEntries.push_back(message);
    //this->entriesLock->unlock();
}

void LogChannel::Flush()
{
    std::list<std::string> entriesCopy;
    //this->entriesLock->lock();
    entriesCopy = this->logEntries;
    this->logEntries.clear();
    //this->entriesLock->unlock();

    for (auto it : entriesCopy)
    {
        std::string str = "[%s] ";
        str.append(it);
        fprintf(this->fileDesc, str.c_str(), this->logTag.c_str());
        //printf(str.c_str(), this->logTag.c_str());
    }
}

}
