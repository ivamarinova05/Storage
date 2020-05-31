#ifndef DATE_H
#define DATE_H

class Date 
{
    private:
    int year;
    int month;
    int day;
    
    void copyDate(const Date&);

    public:
    Date();
    Date(int, int, int);
    Date(const Date&);
    Date& operator=(const Date&);
    ~Date();

    bool operator==(const Date&);
    bool operator!=(const Date&);
    bool operator> (const Date&);
    bool operator>= (const Date&);
    bool operator<= (const Date&);

    friend std::ostream& operator<< (std::ostream&, const Date&);
    friend std::istream& operator>> (std::istream&, Date&);

    void setYear(int);
    void setMonth(int);
    void setDay(int);
    
    void setDate(std::string);

    int getYear() const {return year;}
    int getMonth() const {return month;}
    int getDay() const {return day;}




};

#endif
