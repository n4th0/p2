#ifndef _CATEGORY_H_
#define _CATEGORY_H_
#include <iostream>
#include <vector>
#include "product.h"
using namespace std;

class Category{
    private:
        string name;
        string description;
        vector<Product> products;
    public:
        Category(string name, string description);
        void addProduct(string name, int stock);
};
#endif

