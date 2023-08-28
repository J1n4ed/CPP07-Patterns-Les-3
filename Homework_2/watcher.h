// watcher header

#ifndef HW_2_WATCH_H
#define HW_2_WATCH_H

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

namespace jinx
{

class Vigilant;

class Vigilia {
public:

void AddVigilant(std::weak_ptr<Vigilant> vigilant);
// void RmVigilant(Vigilant * vigilant);
void warning(const std::string& message) const;
void error(const std::string& message) const;
void fatalError(const std::string& message) const;

private:

std::vector<std::weak_ptr<Vigilant>> vigils_;

};

class Vigilant {
public:

    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}

};

class Vigil_Warn : public Vigilant
{
// Warning to console
public:
void onWarning(const std::string& message) override;
};

class Vigil_Err : public Vigilant
{
// Error to log file
public:
void onError(const std::string& message) override;
private:
std::ofstream file_;
};

class Vigil_Fatal_Err : public Vigilant
{
// Fatal error to console and log file
void onFatalError(const std::string& message) override;
private:
std::ofstream file_;
};

} // namespace jinx

/*
QUIS CUSTODIET 
IPSOS CUSTODES
*/

#endif