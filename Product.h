#ifndef PRODUCTS_H
#define PRODUCTS_H
#include <iostream>
#include <string.h>
#include "Date.h"

struct Shelf 
{
    private:
    int number;
    double spaceLeft;

    public:
    Shelf(): number (0), spaceLeft (0) {}
    Shelf(int _number, int _spaceLeft): number(_number), spaceLeft (_spaceLeft) {}

    int getNumber()const {return number;}
    double getSpaceLeft() const { return spaceLeft;}

    void setNumber(int _number) 
    {
        number = _number;
    }
    void setSpace (double _spaceLeft)
    {
        spaceLeft = _spaceLeft;
    }
    Shelf& operator= (const Shelf& other)
    {
        number = other.number;
        spaceLeft = other.spaceLeft;
        return *this;
    }
    void printShelf() const
    {
        std::cout << number << std::endl;
    }    
};


class Product
{
    private:
    std::string name;
    Date expirationDate;
    Date dateOfArrival;
    std::string manufacter;
    std::string unit;
    double quantity;
    Shelf location;
    std::string notes;
    
    void copyProduct(std::string, Date, Date, std::string, std::string, double, Shelf, std::string);

    public:
    Product();
    Product(std::string, Date, Date, std::string, std::string, double, Shelf, std::string);
    Product(const Product&);
    Product& operator= (const Product&);
    ~Product();

    void printProduct() const;
    void inputProduct();

    void setLocation(const Shelf&);
    void setLocation (std::string&);
    void setQuantity(double);
    void setQuantity(std::string&);

    double getQuantity() const {return quantity;}
    std::string getName() const {return name;}
    Shelf& getLocation() {return location;}
    int getLocationNumber () const {return location.getNumber();}
    Date getExpirationDate() const {return expirationDate;}
    Date getArrDate() const {return dateOfArrival;}
    std::string getManufacter() const {return manufacter;}
    std::string getUnit() const  {return unit;}
    std::string getNotes() const {return notes;}
    
    void convert(std::string&);
    friend std::ostream& operator<< (std::ostream&, const Product&) ;


};

#endif
