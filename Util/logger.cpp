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

Logger::Logger() : logChannels(), logEntries()
{
    this->CreateLogChannel("logger_debug", "LGDB", stderr);
    this->EnableLogChannel("logger_debug");
}

Logger::~Logger()
{
    for (auto it : this->logChannels)
    {
        LogChannel *channel = it.second;
        it.second = nullptr;
        delete channel;
    }
}

Logger::Logger(const Logger&) : logChannels(), logEntries()
{

}

Logger& Logger::operator= (const Logger&)
{
    return *this;
}

bool Logger::HasLogChannel(std::string channelName) const
{
    auto it = this->logChannels.find(channelName);
    return (it != this->logChannels.end());
}

void Logger::CreateLogChannel(std::string channelName, std::string tag, FILE* fileDesc)
{
    if (!this->HasLogChannel(channelName))
    {
        LogChannel* channel = new LogChannel(tag, fileDesc);
        this->logChannels[channelName] = channel;
    }
    else
    {
        std::string message = "Tried to recreate log channel with name: ";
        message.append(channelName);
        message.append("\n");
        this->Log("logger_debug", message);
    }
}

void Logger::EnableLogChannel(std::string channelName)
{
    if (this->HasLogChannel(channelName))
    {
        this->logChannels[channelName]->Enable();
    }
    else
    {
        std::string message = "Tried to enable log channel that does't exist with name: ";
        message.append(channelName);
        message.append("\n");
        this->Log("logger_debug", message);
    }
}

void Logger::DisableLogChannel(std::string channelName)
{
    if (this->HasLogChannel(channelName))
    {
        this->logChannels[channelName]->Disable();
    }
    else
    {
        std::string message = "Tried to disable log channel that does't exist with name: ";
        message.append(channelName);
        message.append("\n");
        this->Log("logger_debug", message);
    }
}

bool Logger::IsLogChannelEnabled(std::string channelName) const
{
    if (this->HasLogChannel(channelName))
    {
        return this->logChannels.at(channelName)->IsEnabled();
    }
    else
    {
        return false;
    }
}

void Logger::Log(std::string channelName, std::string message)
{
    if (this->HasLogChannel(channelName))
    {
        if (this->IsLogChannelEnabled(channelName))
        {
            LogChannel* channel = this->logChannels[channelName];
            if (channel->IsEnabled())
            {
                LogEntry entry;
                entry.channel = this->logChannels[channelName];
                entry.message = message;
                this->logEntries.push_back(entry);
            }
        }
    }
    else
    {
        std::string message = "Tried to log on log channel that does't exist with name: ";
        message.append(channelName);
        message.append("\n");
        this->Log("logger_debug", message);
    }
}

void Logger::Flush()
{
    // TODO: figure out mutex stuff

    std::list<LogEntry> entriesClone;
    entriesClone = this->logEntries;
    this->logEntries = std::list<LogEntry>();

    for (auto entry : entriesClone)
    {
        std::string logTag = entry.channel->GetLogTag();
        FILE* fileDesc = entry.channel->GetFileDesc();
        std::string str = "[%s] ";
        str.append(entry.message);
        fprintf(fileDesc, str.c_str(), logTag.c_str());
    }
}

}
