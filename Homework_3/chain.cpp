// chain of responsibility source

#include "chain.h"

#include <exception>
#include <iostream>
#include <memory>
#include <string>

namespace jinx
{
    // Exception

    fatal_exception_handler::fatal_exception_handler(const std::string & msg)
    {
        std::string tmp = "\nFATAL EXCEPTION ENCOUNTERED! Error message: ";
        tmp += msg;
        std::cout << "\nDEBUG: exception msg = " << msg << std::endl;
        msg_ = tmp.data();        
    }

    unknown_exception_handler::unknown_exception_handler(const std::string & msg)
    {
        std::string tmp = "\nUNKNOWN EXCEPTION ENCOUNTERED! Error message: ";
        tmp += msg;
        std::cout << "\nDEBUG: exception msg = " << msg << std::endl;
        msg_ = tmp.data();   
    }
    
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

    void Warning::logEvent(const LogMessage * msg)
    {
        if (msg->type() == WARNING)
        {
            std::cout << "\nDEBUG: WARNING CALLED, MSG: " << msg->message();
        }
        else if (next_)
        {
            next_->logEvent(msg);
        }
    }

    // Log Error    

    void Error::logEvent(const LogMessage * msg)
    {
        if (msg->type() == ERROR)
        {
            std::cout << "\nDEBUG: ERROR CALLED, MSG: " << msg->message();
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
            std::cout << "\nDEBUG: FATAL ERROR CALLED, MSG: " << msg->message();
            throw fatal_exception_handler(msg->message());
        }
        else if (next_)
        {
            next_->logEvent(msg);
        }
    }

    // Log Unknown    

    void Unknown::logEvent(const LogMessage * msg)
    {
        std::cout << "\nDEBUG: UNKNOWN ERROR CALLED, MSG: " << msg->message();      
        throw unknown_exception_handler(msg->message());  
    }

} // namespace jinx