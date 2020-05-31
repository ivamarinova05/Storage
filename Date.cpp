#include <iostream>
#include "Date.h"
#include <string>

void Date::copyDate(const Date& other)
{
    year = other.year;
    month = other.month;
    day = other.day;   
}

Date::Date(): year{0},month{0}, day{0}  {}

Date::Date(int _year,int _month, int _day  ):year{_year}, month {_month}, day {_day}{}

Date::Date(const Date& other)
{
    copyDate(other);    
}

Date& Date::operator=(const Date& other)
{
    if (this != &other)
    {
        copyDate(other);
    }
    return *this;
}

Date::~Date()
{

}

bool Date::operator> (const Date& other)
{
    int lyear,ryear;
    lyear = this->year * 10000 + this->month * 100 + this->day;
    ryear = other.year * 10000 + other.month * 100 + other.day;
    if( lyear > ryear )
        return true;
    
    return false;
}

bool Date::operator>= (const Date& other)
{
    int lyear,ryear;
    lyear = this->year * 10000 + this->month * 100 + this->day;
    ryear = other.year * 10000 + other.month * 100 + other.day;
    if( lyear >= ryear )
        return true;
    
    return false;
}

bool Date::operator<= (const Date& other)
{
    int lyear,ryear;
    lyear = this->year * 10000 + this->month * 100 + this->day;
    ryear = other.year * 10000 + other.month * 100 + other.day;
    if( lyear <= ryear )
        return true;
    
    return false;
}



std::ostream& operator<<(std::ostream& out, const Date& date)
{
    out << date.getYear() << "-";
    if (date.getMonth() < 10)
    {
        out << "0";
    }
    out << date.getMonth() << "-";
    if (date.getDay() <10 )
    {
        out << "0";
    }
    out << date.getDay();
    return out;

}
void Date::setYear(int _year)
{
    year = _year;
}

void Date::setMonth(int _month)
{
    month = _month;
}

void Date::setDay(int _day)
{
    day = _day;
}

void Date::setDate(std::string _date)
{
    year = (_date[0] - '0')*1000 + (_date[1] - '0')*100 + (_date[2] - '0')*10 + (_date[3] - '0');
    month = (_date[5] - '0')*10 + (_date[6] - '0');
    day = (_date[8] - '0')*10 + (_date[9] - '0');
}

std::istream& operator>> (std::istream& in, Date& date)
{
    std::string d;
    in >> d;
    date.setYear((d[0] - '0')*1000 + (d[1] - '0')*100 + (d[2] - '0')*10 + (d[3] - '0'));
    date.setMonth((d[5] - '0')*10 + (d[6] - '0'));
    if(date.getMonth() < 1 || date.getMonth() > 12)
    {
        std::cout << "Invalid date\n";
    }
    date.setDay( (d[8] - '0')*10 + (d[9] - '0'));
    return in;
}

bool Date::operator==(const Date& other)
{
    return (day == other.day && month == other.month && year == other.year);
}
bool Date::operator!=(const Date& other)
{
    return !operator==(other);
}
