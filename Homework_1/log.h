// logger header

#ifndef HW_1_LOG_H
#define HW_1_LOG_H

#include <string>
#include <fstream>

namespace jinx
{

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string & message) = 0;
    virtual void print(LogCommand *) = 0;
};

} // namespace jinx

namespace jinx
{

class LogTerminal : public jinx::LogCommand {

    private:

    std::string message_;

    public:

    void print(const std::string & message);

    void print(jinx::LogCommand * command) override;

    LogTerminal() = delete;
    
    LogTerminal(std::string);

};

class LogFile : public jinx::LogCommand {

    private:

    std::string message_;
    std::ofstream file_;

    public:

    void print(const std::string & message);

    void print(jinx::LogCommand * command) override;

    LogFile() = delete;

    LogFile(std::string);

};
    
} // namespace jinx

#endif