#include "Log.h"

#include <iostream>

Log::Log() = default;

Log::Log(std::vector<std::string> mod, std::vector<Date> frame, std::vector<Date> all):
            modifications (mod), frameDates (frame), allDates(all) {}

Log::~Log() = default;

void Log::sortDates()
{
    for (int i = 0; i < allDates.size() - 1; i++)
    {
        for ( int j = i+1; j < allDates.size(); j++)
        {
            if (allDates[i] > allDates[j])
            {
                Date save;
                save = allDates[i];
                allDates[i] = allDates[j];
                allDates[j] = save;
                std::swap (modifications[i], modifications[j]);
            }
        }
    }
}

void Log::printModifications()
{
    for (int i = 0; i< allDates.size(); i++)
    {
        if (allDates[i] >= frameDates[0] && allDates[i] <= frameDates[1])
        {
            std::cout << modifications[i] << "\n";
        }
    }
}

void Log::printAllInfo()
{
    for (std::string info: modifications)
    {
        std::cout << info << "\n";
    }
}
