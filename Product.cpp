#include "Product.h"
#include "Functions.h"
#include "Date.h"
#include <iostream>
#include <string.h>

void Product::copyProduct(std::string _name, Date _expirationDate, Date _dateOfArrival, std::string _manufacter, 
                          std::string _unit, double _quantity, Shelf _location, std::string _notes)
{
    name = _name;
    expirationDate = _expirationDate;
    dateOfArrival = _dateOfArrival;
    manufacter =  _manufacter;
    unit = _unit;
    quantity = _quantity;
    location = _location;
    notes = _notes;
}

Product::Product() = default;
Product::Product(std::string _name, Date _expirationDate, Date _dateOfArrival, std::string _manufacter, 
                std::string _unit, double _quantity, Shelf _location, std::string _notes)
{
    copyProduct(_name, _expirationDate, _dateOfArrival, _manufacter, _unit, _quantity, _location, _notes);   
}

Product::Product(const Product& other)
{
    copyProduct(other.name, other.expirationDate, other.dateOfArrival, other.manufacter, other.unit, other.quantity,
                other.location, other.notes);
}

Product& Product::operator=(const Product& other)
{
    if (this != &other)
    {
        copyProduct(other.name, other.expirationDate, other.dateOfArrival, other.manufacter, other.unit, other.quantity,
                    other.location, other.notes);
    }
    return *this;
}

Product::~Product() = default;

void Product::printProduct() const
{
    std::cout << "Product name: " << name << std::endl
              << "Manufacter: " << manufacter << std::endl
              << "Quantity: " << quantity << unit << std::endl
              << "Location: shelf #";
              location.printShelf();
              std::cout << "Notes: " << notes << std::endl;
}

std::ostream& operator<< (std::ostream& out , const Product& p)
{
    out << p.getName() << " "
        << p.getExpirationDate() << " "
        << p.getArrDate() << " "
        << p.getManufacter() << " "
        << p.getUnit() << " "
        << p.getQuantity() << " "
        << p.getLocationNumber() << " "
        << p.getNotes() << std::endl;
    return out;

}


void Product::setLocation(const Shelf& s)
{
    location = s;
}

void Product::setLocation (std::string& str)
{
    int number = 0;
    for (int i=0; i<str.size(); i++)
    {
        number = number*10 + (str[i] - '0');  
    }
    Shelf newShelf (number, 500);
    this->setLocation(newShelf);

}
void Product::setQuantity(double q)
{
    quantity = q;
}
void Product::inputProduct()
{
    std::cout << "Product name: ";
    std::cin >> name;
    std::cout << "Expiration date: ";
    std::cin >> expirationDate;
    std::cout << "Date of arrival: ";
    std::cin >> dateOfArrival;
    std::cout << "Manufacter: ";
    std::getline(std::cin, manufacter) ;
    std::getline(std::cin, manufacter) ;
    std:: cout << "Unit (kg/l): ";
    std::cin >> unit;
    if (unit != "kg" && unit != "l")
    {
        bool validUnit = false;
        while (!validUnit)
        {
            std::cout << "Invalid unit!\nUnit: ";
            std::cin >> unit;
            if (unit == "kg" || unit == "l") 
            {
                validUnit = true;
            }
        }
        
    }
    std::cout << "Quantity: ";
    std::cin >> quantity;
    std::cout << "Notes: ";
    std::getline(std::cin, notes);
    std::getline(std::cin, notes);
}

void Product::setQuantity(std::string& str)
{
    int divider = 1;
    bool div = false;
    quantity=0;
    for (int i = 0; i < str.size(); i++)
    {
        if (div)
            divider *= 10;
        
        if (str[i] == '.')
        {
            div = true;
        }
        else 
        {
            quantity = quantity*10 + (int(str[i]) - '0');

        }
    }
    quantity /= divider;
}

void Product::convert(std::string& str)
{
    
    name = Functions::helpConvert(str);

    expirationDate.setDate(Functions::helpConvert(str));

    dateOfArrival.setDate(Functions::helpConvert(str));

    manufacter = Functions::helpConvert(str);

    unit = Functions::helpConvert(str);

    std::string helper = Functions::helpConvert(str);

    this->setQuantity(helper);

    helper = Functions::helpConvert(str);

    this->setLocation(helper);

    notes = str;

}
