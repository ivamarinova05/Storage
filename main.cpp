#include <iostream>
#include <cstring>
#include <string>
#include "Product.h"
#include "Date.h"
#include "CommandLineReader.h"
#include "Storage.h"
#include <vector>
#include <ctime>
#include <fstream>

void CLR(std::string command, std::string fileName, bool firstTime)
{
    Storage storage;
    
    while(command != "exit")
    {
        if ( !firstTime )
        {
            std::cout << ">_";
            std::cin >> command;
        }
        firstTime = false;
        if (command == "add")
        {
            storage.add();   
        }
        else if (command == "open")
        {
            fileName = CommandLineReader::ReadFile(storage.getProducts(), storage.getToPrint());
        }
        else if(command == "print")
        {
           storage.print();
        }
        else if(command == "help")
        {
           CommandLineReader::help();
        }
        else if (command == "remove")
        {
            CommandLineReader::remove(storage.getProducts());
        }
        else if (command == "clean")
        {
            storage.clean();
        }

        else if (command == "save")
        {
            CommandLineReader::saveas(storage.getProducts(), fileName);
        }

        else if (command == "saveas")
        {
            std::string fileName;
            std::cin >> fileName;
            CommandLineReader::saveas(storage.getProducts(), fileName);
        }
        else if (command == "close")
        {
            storage.removeAll();
        }

        else if (command == "log")
        {
            CommandLineReader::log();
        }
        else if (command == "exit")
        {
            std::cout << "Exiting the program...";
            continue;
        } 
        
        else 
        {
            std::cout << "Command not found!\n";
        }
    }

}


int main()
{
    std::string command;
    std::string fileName;
    std::cout << "Welcome!\n" << "If you need help using this app please type help!\n";
    std::cout << ">_";
    std::cin >> command;
    while ( command != "open" )
    {
        std::cout << "You need to open a file first!\n>_";
        std::cin >> command;
    }
    CLR( command, fileName, true );
    return 0;

}
