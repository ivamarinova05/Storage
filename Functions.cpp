#include <iostream>
#include <string>
#include <vector>
#include "Date.h"
#include "Product.h"
#include "Functions.h"
#include <ctime>

std::string Functions::helpConvert (std::string& str)
{
    int pos = str.find(" ");
    std::string option;
    option = str.substr(0,pos);
    str.erase(0, pos+1);
    return option;
}

Date Functions::getCurrentDate ()
{
    Date currentDate;
    time_t t = time(0);
    struct tm* now = localtime( & t );
    currentDate.setYear(now->tm_year + 1900);
    currentDate.setMonth(now->tm_mon + 1);
    currentDate.setDay(now->tm_mday); 
    return currentDate;
}

std::vector<Date> Functions::getDates()
{
    std::vector<Date> Finaldates;

    std::string dates;
    getline(std::cin, dates);
    int pos = dates.find(" ");
    while ( pos == 0)
    {
        dates = dates.substr(1);
        pos = dates.find(" ");
    }

    while ( dates.empty() )
    {
        std::cout << "Please input dates: ";
        getline(std::cin, dates);
        getline(std::cin, dates);
    }
    
    std::string from;
    from = dates.substr(0, pos);
    dates.erase(0, pos + 1);
    
    Date fromDate;
    fromDate.setDate(from);

    std::string to;
    pos = dates.find(" ");
    if (pos == -1)
    {
        to = dates;
    }
    else 
    {
        to = dates.substr(0, pos);
    }
    Date toDate;
    toDate.setDate(to);

    Finaldates.push_back(fromDate);
    Finaldates.push_back(toDate);
    return Finaldates;
}

std::string Functions::removeSpaces(std::string word)
{
    int pos = word.find(" ");
    while ( pos == 0 )
    {
        word = word.substr(1);
        pos = word.find(" ");
    }
    return word;
}
