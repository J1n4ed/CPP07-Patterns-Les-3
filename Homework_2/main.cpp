// main source

#include "watcher.h"

#include <iostream>
#include <memory>

int main(int argc, char ** argv)
{
    jinx::Vigilia subject;

    std::cout << "Exec start.\n";
    
    // create watchers

    std::shared_ptr<jinx::Vigil_Warn> SharedVigilWarn(new jinx::Vigil_Warn);
    std::weak_ptr<jinx::Vigilant> WeakVigilWarn(SharedVigilWarn);
    subject.AddVigilant(WeakVigilWarn);

    std::shared_ptr<jinx::Vigil_Err> SharedVigilErr(new jinx::Vigil_Err);
    std::weak_ptr<jinx::Vigilant> WeakVigilErr(SharedVigilErr);
    subject.AddVigilant(WeakVigilErr);

    std::shared_ptr<jinx::Vigil_Fatal_Err> SharedVigilFatErr(new jinx::Vigil_Fatal_Err);
    std::weak_ptr<jinx::Vigilant> WeakVigilFatErr(SharedVigilFatErr);
    subject.AddVigilant(WeakVigilFatErr);    

    std::cout << "\nVigilants created.\n";

    // call 50 events of different types
    for (int i = 0; i < 50; ++i)
    {
        if (i % 2 == 0)
        {
            subject.warning("Warning called");
        }
        else if (i % 3 == 0)
        {
            subject.error("Error called");
        }
        else
        {
            subject.fatalError("Fatal error called");
        }
    }

    std::cout << "\nExec finished.\n";

    // exit
    std::cout << std::endl;
    std::cout << "PRESS ENTER ...";
    std::cin.get();
    return EXIT_SUCCESS;
}