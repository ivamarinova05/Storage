#include "Storage.h"
#include "Product.h"
#include "Date.h"
#include "Functions.h"
#include "CommandLineReader.h"
#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>

void Storage::createShelf(Product& p)
{
    Shelf newShelf(shelfs.size()+1, 500); 
    p.setLocation(newShelf);
    newShelf.setSpace(newShelf.getSpaceLeft() - p.getQuantity());
    shelfs.push_back(newShelf);
}


void Storage::setShelf(Product& p)
{
    if(shelfs.empty())
    {
        createShelf(p);
    }
    else 
    {
        bool added = false;
        for (int i = 0; i < shelfs.size(); i++)
        {
            if (shelfs[i].getSpaceLeft() >= p.getQuantity())
            {
                p.setLocation(shelfs[i]);
                shelfs[i].setSpace(shelfs[i].getSpaceLeft() - p.getQuantity());
                added = true;
                break;
            }
        }
        if (!added)
        {
            createShelf(p);
        }
    }

}

bool Storage::searchProduct (Product& p)
{
    bool added = false;
    for (int i = 0; i < products.size(); i++)
    {
        if (products[i].getName() == p.getName())
        {
            added = true;
            if (products[i].getExpirationDate() == p.getExpirationDate()
                && products[i].getLocation().getSpaceLeft() >= p.getQuantity())
            {
                p.setLocation(products[i].getLocation());
            }
            else 
            {
                setShelf(p);
            }

            if (products[i].getExpirationDate() != p.getExpirationDate())
            {
                int save = products[i].getLocation().getSpaceLeft();
                products[i].getLocation().setSpace(0);
                setShelf(p);
                products[i].getLocation().setSpace(save);

            }

        }
    }
    return added;//връща true ако го е поставило някъде
}

void Storage::searchPrint(int i)
{
    if(!toPrint[i])
    {
        toPrint[i] = true;
        double quantity = products[i].getQuantity();
        for (int j = i+1; j < products.size(); j++)
        {
            if (products[i].getName() == products[j].getName())
            {
                toPrint[j] = true;
                quantity += products[j].getQuantity();
            }

        }
        std::cout << "Product name: " << products[i].getName() << std::endl
                  << "Manufacter: " << products[i].getManufacter() << std::endl
                  << "Quantity: " << quantity << products[i].getUnit() << "\n\n";

    }
}

void Storage::clean()
{
    Date currentDate = Functions::getCurrentDate();
    auto it = products.begin();
    for (int i=0; i < products.size(); i++, it++)
    {
        if (currentDate > products[i].getExpirationDate())
        {
            products.erase(it);
            i--;
            it--;
        }
    }
    std::cout << "All expired products have been removed successfully!\n";
    std::ofstream logFile ("log.txt", std::ios::out | std::ios::app);
    logFile << currentDate << " The storage has been cleared of all expired products.\n";
    logFile.close();
}

void Storage::print()
{
    if (products.empty())
    {
        std::cout << "There are no products available!\n";
    }
    for (int i = 0; i < products.size(); i++)
    {
        searchPrint(i);
    }
    for(int i=0; i<toPrint.size(); i++)
    {
        toPrint[i] = false;
    }
}

void Storage::add()
{
    Product newProduct;
    newProduct.inputProduct();
    if (!searchProduct(newProduct))
    {
        setShelf(newProduct);
    }
    products.push_back(newProduct);
    toPrint.push_back(false);
    std::cout << "\nProduct has been added successfully!\n";
    std::ofstream logFile ("log.txt", std::ios::out | std::ios::app);
    logFile << newProduct.getArrDate() << " "
            << newProduct.getQuantity() << newProduct.getUnit() << " of " 
            << newProduct.getName() << " arrived in the storage.\n";
    logFile.close();
}

void Storage::removeAll()
{
    products.clear();
    toPrint.clear();
    shelfs.clear();
    std::cout << "All data has been cleared!\n";
}
