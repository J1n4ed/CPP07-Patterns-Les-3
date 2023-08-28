// watcher source

#include "watcher.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

namespace jinx
{
    
// Vigilia

void Vigilia::AddVigilant(std::weak_ptr<Vigilant> vigilant)
{
    vigils_.push_back(vigilant);
}

/*
void Vigilia::RmVigilant(Vigilant * vigilant)
{
    std::vector<Vigilant *>::iterator it = std::remove(vigils_.begin(), vigils_.end(), vigilant);
    vigils_.erase(it, vigils_.end());
}
*/

void Vigilia::warning(const std::string & message) const
{
    for (auto unit : vigils_)
    {
        // check if alive
        if (auto strong_ptr = unit.lock())
            strong_ptr->onWarning("WARNING LOGGED\n");
    }
}

void Vigilia::error(const std::string & message) const
{
    for (auto unit : vigils_)
    {
        // check if alive
         if (auto strong_ptr = unit.lock())
            strong_ptr->onError("ERROR LOGGED\n");
    }
}

void Vigilia::fatalError(const std::string & message) const
{
    for (auto & unit : vigils_)
    {
         // check if alive
         if (auto strong_ptr = unit.lock())
            strong_ptr->onFatalError("FATAL ERROR LOGGED\n");
    }
}

// On Warning

void Vigil_Warn::onWarning(const std::string& message)
{
    std::cout << "WARNING: " << message << '\n';
}

// On Error

void Vigil_Err::onError(const std::string& message)
{
    file_.open ("log.txt", std::ios_base::app);
    file_ << "ERROR: " << message << '\n';
    file_.close();
}

// On Fatal Error

void Vigil_Fatal_Err::onFatalError(const std::string& message)
{
    std::cout << "FATAL ERROR: " << message << '\n';
    file_.open ("log.txt", std::ios_base::app);
    file_ << "FATAL ERROR: " << message << '\n';
    file_.close();
}

} // namespace jinx