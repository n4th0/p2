
#include "coordenada.h"

Coordenada::Coordenada(float cx, float cy){
    Coordenada::x=cx;
    Coordenada::y=cy;

}

// Coordenada::Coordenada(){
//     Coordenada::x=0;
//     Coordenada::y=0;
// 
// }

Coordenada::Coordenada(const Coordenada &){
    // TODO hacer la funcion (no se como se hace)


}
Coordenada::~Coordenada(){
    // TODO hacer la funcion (no se como se hace)

}
float Coordenada::getX() const{
    return Coordenada::x;

}

float Coordenada:: getY() const{
    return Coordenada::y;
}

void Coordenada::setX(float cx){
    Coordenada::x=cx;
    return;
}

void Coordenada::setY(float cy){
    Coordenada::y=cy;
    return;
}

