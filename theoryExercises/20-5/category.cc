#include "category.h"
#include "product.h"
#include <iostream>
using namespace std;

Category::Category(string name, string description){
    this->name = name;
    this->description = description;
}

void Category::addProduct(string name, int stock){
    Product product(name);
    product.setStock(stock);
    products.push_back(product);

}
