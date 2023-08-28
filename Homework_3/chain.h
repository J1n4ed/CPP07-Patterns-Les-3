// chain of responsibility header

#ifndef HW_3_CHAIN_H
#define HW_3_CHAIN_H

#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

namespace jinx
{
    enum Type
    {
        FATAL_ERROR,
        ERROR,
        WARNING,
        UNKNOWN
    };

    // Exceptions

    class fatal_exception_handler : public std::runtime_error
    {
        public:

        fatal_exception_handler(const std::string & msg = "") : msg_(msg), std::runtime_error(msg)
        {

        }  

        std::string & what()
        {
            msg_ = "> Fatal Exception encountered, message: " + msg_;

            return msg_;
        }

        private:
        std::string msg_;     
    };

    class unknown_exception_handler : public std::runtime_error
    {
        public:

        unknown_exception_handler(const std::string & msg = "") : msg_(msg), std::runtime_error(msg)
        {

        }  

        std::string & what()
        {
            msg_ = "> Unknown Exception encountered, message: " + msg_;

            return msg_;
        }

        private:
        std::string msg_;    
    };

    class Warning;
    class Error;
    class Fatal;
    class Unknown;

    class LogMessage {
    public:
        Type type() const;
        const std::string& message() const; 

        LogMessage() = delete;
        LogMessage(std::string, Type);
        LogMessage(std::string);

    private:
    Type type_;
    std::string message_;
    };

    class Log
    {
        public:

        virtual void logEvent(const LogMessage * msg) = 0;     
        void setNext(Log *);    

        virtual ~Log() = default;  

        protected:

        Log * next_;
        
    };    

    class Warning : public Log
    {  
        public:

        void logEvent(const LogMessage * msg) override;     
    };

    class Error : public Log
    {
        public:

        void logEvent(const LogMessage * msg) override;        

        private:

        std::fstream file_;
    };

    class Fatal : public Log
    {
        public:
        
        void logEvent(const LogMessage * msg) override;        

        private:
        std::fstream file_;
    };

    class Unknown : public Log
    {
        public:

        void logEvent(const LogMessage * msg) override;        

        private:
    };

} // namespace jinx

#endif