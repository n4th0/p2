#ifndef _PRODUCT_H_
#define _PRODUCT_H_
#include <iostream>
using namespace std;

class Product{
    private:
        static const int MIN_STOCK = 5;
        string name;
        int stock;
    public:
        Product(string name);
        bool sell(int quantity);
        void setStock(int stock);
        void setName(string name);
        int getStock() const;
        string getName() const;

};

#endif
