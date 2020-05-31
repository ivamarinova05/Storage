#ifndef STORAGE_H
#define STORAGE_H
#include <vector>
#include <string>
#include "Product.h"

class Storage
{
    private:
    std::vector<Product> products;
    std::vector<Shelf> shelfs;
    std::vector<bool> toPrint;


    public:
    void createShelf(Product&);
    void setShelf(Product&);
    bool searchProduct (Product& p);
    void searchPrint(int);

    void clean();
    void print();
    void add();
    void removeAll();

    std::vector<Product>& getProducts() {return products;}
    std::vector<Shelf>& getShelfs() {return shelfs;}
    std::vector<bool>& getToPrint() {return toPrint;}




};

#endif
