#ifndef LOG_H
#define LOG_H


#include <vector>
#include <string>

#include "Date.h"
class Log
{
    private:
    std::vector<std::string> modifications;
    std::vector<Date> frameDates;
    std::vector<Date> allDates;

    public:
    Log();
    Log(std::vector<std::string>, std::vector<Date>, std::vector<Date>);
    ~Log();

    void sortDates();
    void printModifications();
    void printAllInfo();


};

#endif
