#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <vector>
#include "Date.h"
#include "Product.h"

class Functions
{
    public:
    static std::string helpConvert (std::string&);
    static Date getCurrentDate ();
    static std::vector<Date> getDates ();
    static std::string removeSpaces(std::string);
};


#endif
