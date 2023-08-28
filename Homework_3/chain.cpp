// chain of responsibility source

#include "chain.h"

#include <exception>
#include <iostream>
#include <memory>
#include <string>

namespace jinx
{    
    // Log message class

    Type LogMessage::type() const
    {
    return type_;
    }

    const std::string & LogMessage::message() const
    {
        return message_;
    }

    LogMessage::LogMessage(std::string message, Type type) : message_(message), type_(type) {}

    LogMessage::LogMessage(std::string message) : message_(message), type_(jinx::UNKNOWN) {}

    // Log hierarhy    

    // LOG

    void Log::setNext(Log * nextLogger)
    {
        next_ = nextLogger;
    }

    // Log Warning   

    /*
    Обработчик предупреждения должен напечатать сообщение в консоль.
    */

    void Warning::logEvent(const LogMessage * msg)
    {
        if (msg->type() == WARNING)
        {
            std::cout << "\nWARNING CALLED, MSG: " << msg->message();
        }
        else if (next_)
        {
            next_->logEvent(msg);
        }
    }

    // Log Error    

    /*
    Обработчик обычной ошибки должен записать её в файл по указанному пути
    */

    void Error::logEvent(const LogMessage * msg)
    {
        if (msg->type() == ERROR)
        {
            file_.open("log.txt", std::ios::app);
            file_ << "ERROR CALLED, MSG: " << msg->message() << '\n';        
            file_.close();
        }
        else if (next_)
        {
            next_->logEvent(msg);
        }
    }

    // Log Fatal Error    

    void Fatal::logEvent(const LogMessage * msg)
    {

    /*
    Обработчик фатальной ошибки должен выбросить исключение с текстом сообщения, 
    потому что предполагается, что программа должна прекратить 
    выполнение после возникновения фатальной ошибки.
    */

        if (msg->type() == FATAL_ERROR)
        {
            file_.open("log.txt", std::ios::app);
            file_ << "FATAL ERROR CALLED, MSG: " << msg->message() << '\n';        
            file_.close();
            throw fatal_exception_handler(msg->message());
        }
        else if (next_)
        {
            next_->logEvent(msg);
        }
    }

    // Log Unknown    

    /*
    Обработчик неизвестного сообщения должен выбросить исключение с текстом о необработанном сообщении
    */

    void Unknown::logEvent(const LogMessage * msg)
    {
        throw unknown_exception_handler(msg->message());  
    }

} // namespace jinx