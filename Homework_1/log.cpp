// logger source

#include "log.h"

#include <iostream>
#include <fstream>
#include <string>

namespace jinx
{

// Terminal logger

LogTerminal::LogTerminal(std::string message)
{
    if (!message.empty())
    message_ = message;   
}

void LogTerminal::print(const std::string & message)
{
    std::cout << "LOG EVENT: " << message << '\n';
}

void LogTerminal::print(jinx::LogCommand * command)
{
    command->print(message_);
}

// File logger

LogFile::LogFile(std::string message)
{
    if (!message.empty())
        message_ = message;
}

void LogFile::print(const std::string & message)
{
    file_.open ("log.txt", std::ios_base::app);
    file_ << "LOG EVENT: " << message << '\n';
    file_.close();
}

void LogFile::print(jinx::LogCommand * command)
{
    command->print(message_);
}

} // namespace jinx