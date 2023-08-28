// main source

#include "chain.h"

#include <iostream>
#include <memory>

int main(int argc, char ** argv)
{
    jinx::Log * warning_handler  = new jinx::Warning;
    jinx::Log * error_handler    = new jinx::Error;
    jinx::Log * fatal_handler    = new jinx::Fatal;
    jinx::Log * unknown_handler  = new jinx::Unknown;

    /*
    PRIORITY:

    фатальная ошибка,
    ошибка,
    предупреждение,
    неизвестное сообщение.
    */

    warning_handler->setNext(unknown_handler);
    error_handler->setNext(warning_handler);
    fatal_handler->setNext(error_handler);

    //

    int i = 0;
    bool run = true;

    std::cout << "\nExecution start.\n\n";

    while (run)
    {

    try
    {
        if (i++ < 30)
        {
            // exit condition
            if (i == 29)
            {
                run = false;
            }

            if (i % 5 == 0)
            {
                fatal_handler->logEvent(new jinx::LogMessage( "> Error message of warning error type\n", jinx::WARNING));
            }
            else if (i % 3 == 0)
            {
                fatal_handler->logEvent(new jinx::LogMessage( "> Error message of error error type\n", jinx::ERROR));
            }
            else if (i % 2 == 0)
            {
                fatal_handler->logEvent(new jinx::LogMessage( "> Error message of fatal error type\n", jinx::FATAL_ERROR));
            }
            else
            {
                fatal_handler->logEvent(new jinx::LogMessage( "> Error message of unknown type\n"));
            }            
        }
    }
    catch(const std::exception & e)
    {
        std::cerr << "(!) EXCEPTION: " << e.what() << '\n';
    }

    } // while

    std::cout << "\nExecution finished.\n\n";

    // Exit

    std::cout << std::endl;
    std::cout << "PRESS ENTER ...";
    std::cin.get();
    return EXIT_SUCCESS;

} // main