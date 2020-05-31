#include "Product.h"
#include "Date.h"
#include "Functions.h"
#include "CommandLineReader.h"
#include "Log.h"

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>




void CommandLineReader::help ()
{
     std::cout <<  "The following commands are being supported:\n" <<
                          "open <file>      ->   opens <file>. If a file with that name does not exist a new one is being created.\n" <<
                          "close            ->   closes currently opened file\n" <<
                          "save             ->   saves the currently opened file\n" <<
                          "saveas<file>     ->   saves the currently opened file in <file>\n" <<
                          "exit             ->   exits the program\n" <<
                          "add              ->   adds a new product\n" <<
                          "print            ->   prints all products available\n" <<
                          "remove           ->   removes the amount you've stated from the product you've stated\n" <<
                          "clean            ->   cleans the storage from all expired products \n" <<
                          "log <from> <to> ->    gives information for all changes made in that period\n";

}

void CommandLineReader::remove(std::vector<Product>& products)
{
    std::string name;
    std::cout << "Product name: ";
    std::cin >> name;
    double quantity;
    std::cout << "Quantity: ";
    std::cin >> quantity;
    double quantityToLog = quantity;
    std::vector<Product> toRemove;
    std::vector<int> index;
    double sumQuantity = 0;
    for (int i = 0; i < products.size(); i++)
    {
        if (name == products[i].getName())
        {
            toRemove.push_back(products[i]);
            index.push_back(i);
            sumQuantity += products[i].getQuantity();
        }
        
    }
    if (sumQuantity < quantity)
    {
        std:: cout << "Sorry, not enough quantity in stock!\n";
        return;
    }
    else 
    {
        for (int i=0; i < toRemove.size() - 1; i++)
        {
            for(int j = i+1; j < toRemove.size(); j++)
            {
                if (toRemove[i].getExpirationDate() > toRemove[j].getExpirationDate())
                {
                    std::swap(toRemove[i], toRemove[j]);
                    std::swap(index[i], index[j]);
                }
            }
        }        
        auto it = toRemove.begin();
        auto it2= index.begin();
        for(int i=0; i < toRemove.size(); i++,it++)
        {
            if(toRemove[i].getQuantity() > quantity)
            {
                toRemove[i].setQuantity(toRemove[i].getQuantity() - quantity);
                products[index[i]].setQuantity(products[index[i]].getQuantity() - quantity);
                quantity = 0;
            }
            else if (toRemove[i].getQuantity() == quantity)
            {
                toRemove.erase(it);
                products.erase(products.begin() + index[i]);
                index.erase(it2);
                quantity = 0;
            }
            else 
            {
                quantity -= toRemove[i].getQuantity();
                toRemove.erase(it);
                products.erase(products.begin() + index[i]);
                index.erase(it2);
                i--;
                it--;
            }
            if (quantity == 0) break;
        }
    }
    std::cout << "\nProduct has been removed successfully!\n";
    std::ofstream logFile ("log.txt", std::ios::out | std::ios::app);
    logFile << Functions::getCurrentDate() << " " << quantityToLog << toRemove[0].getUnit() 
                                            << " of " << name << " have been removed from the storage.\n";
    logFile.close();
}

int CommandLineReader::getNumber (std::string a)
{
    int n = a.size();
    int x = 0;
    for (int i=0; i < n; i++)
    {
        x = x*10 + (int(a[i] - '0'));

    }
    return x;
}

std::string CommandLineReader::ReadFile (std::vector<Product>& products, std::vector<bool>& print)
{
    std::string fileName;
    getline (std::cin, fileName);
    fileName = Functions::removeSpaces(fileName);
    while ( fileName.size() == 0 )
    {
        std::cout << "Please input file: ";
        getline (std::cin, fileName);
        fileName = Functions::removeSpaces(fileName);
    }
    std::string a;
    std::fstream inFile (fileName, std::ios::in | std::ios::out | std::ios::app);
    int number;
    if(inFile.is_open())
    {
        std::getline(inFile, a);
        number = getNumber(a);
        inFile.close();
    }
    else
    {
        std::cout<<"Unable to open file!\n";
    }

    inFile.open(fileName);
    if(inFile.is_open())
    {
        int id=0;
        while(getline(inFile, a))
        {
            if(id > 0)
            {
                std::string str = a;
                Product newProduct;
                newProduct.convert(a);
                products.push_back(newProduct);
                print.push_back(false);
            }
            id++;
        }
        inFile.close();
    }
    std::cout << "Successfully opened " << fileName << "!\n";
    return fileName;
}


void CommandLineReader::saveas(std::vector<Product>& products, std::string fileName)
{
    
    std::ofstream outFile (fileName);
    outFile << products.size() << std::endl;
    for (int i = 0; i < products.size(); i++)
    {
        outFile << products[i];
    }
    std::cout << "All changes have successfully been saved to "<< fileName << "!\n";

}

void CommandLineReader::log()
{
    std::vector<Date> frameDates;
    std::vector<Date> allDates;
    frameDates = Functions::getDates();
    
    std::ifstream logFile ("log.txt");
    std::vector<std::string> modifications;
    std::string line;
    while ( getline(logFile, line) )
    {
        std::string currentDate;
        currentDate = line.substr(0, 10);
        modifications.push_back(line);

        Date current;
        current.setDate(currentDate);
        allDates.push_back(current);  
    }
    logFile.close();
    Log log(modifications, frameDates, allDates);
    
    log.sortDates();
    log.printModifications();
}
