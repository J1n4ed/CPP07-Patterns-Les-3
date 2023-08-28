// main functiuon

#include "log.h"

#include <iostream>
#include <vector>

int main(int argc, char ** argv)
{    
    std::vector<jinx::LogCommand *> pipe;

    std::cout << "Message to log\n\n";

    for (int i = 0; i < 10; ++i)
    {
        if (i % 2 == 0)
        {
            pipe.push_back(new jinx::LogFile("log to file"));
        }
        else
        {
            pipe.push_back(new jinx::LogTerminal("log to Terminal"));
        }
    }

    for (const auto & exec : pipe)
    {
        exec->print(exec);
    }

    // exit

    std::cout << std::endl;
    std::cout << "PRESS ENTER ... ";
    std::cin.get();
    return EXIT_SUCCESS;
}