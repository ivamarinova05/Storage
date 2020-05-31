#ifndef COMMANDLINEREADER_H
#define COMMANDLINEREADER_H
#include <iostream>
#include <string>
#include <vector>

class CommandLineReader
{
    
    static int getNumber(std::string);

    public:
    static std::string ReadFile (std::vector<Product>&, std::vector<bool>&);

    static void open();
    static void help();
    static void saveas(std::vector<Product>&, std::string);
    static void remove(std::vector<Product>&);
    static void log ();
};
#endif
