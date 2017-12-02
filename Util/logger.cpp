#include "logger.hpp"

namespace Util
{

Logger::Logger() : logChannels()
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
                channel->AddLogEntry(message);
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

void Logger::FlushAll()
{
    for (auto it : this->logChannels)
    {
        LogChannel *channel = it.second;
        channel->Flush();
    }
}

}
