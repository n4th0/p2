
#include "product.h"
#include <stdexcept>
#include <string>
using namespace std;

Product::Product(string name){
    this->name = name;
    this->stock = 0;
}

bool Product::sell(int quantity){
    if (quantity > this->stock) {
        throw invalid_argument(to_string(quantity));
    }
    this->stock -= quantity;

    return (this->stock > MIN_STOCK);
}

void Product::setStock(int stock){
    this->stock = stock;
}

void Product::setName(string name){
    this->name = name;
}

int Product::getStock() const{
    return stock;
}

string Product::getName() const{
    return name;
}
