#include "coordenada.h"

#include <iostream>


int main(){
    Coordenada c(10, 10);
    c.setX(20);

    std::cout << c.getX()<<std::endl;
    std::cout << c.getY()<<std::endl;

    return 0;
}
