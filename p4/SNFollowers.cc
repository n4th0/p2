
#include "SNData.h"
#include "SNFollowers.h"
#include "Util.h"
#include <stdexcept>
#include <string>
#include <cstring>
using namespace std;

/*
 * Constructor que crea un nuevo objeto con los datos pasados por parámetros, y con un valor inicial del dinero 
 * (money) de 0. Si la red social no existe, se lanzará la excepción EXCEPTION_UNKNOWN_SN; 
 * si el número inicial de seguidores es menor que 0 se lanzará la excepción estándar 
 * invalid_argument pasándole como parámetro dicho número (convertido a cadena con la función to_string, 
 * ya que el parámetro de esa excepción debe ser una cadena).
 * */
SNFollowers::SNFollowers(std::string name, int initialFollowers){
    if(!SNData::checkSN(name)){
        throw EXCEPTION_UNKNOWN_SN;
    }

    if (initialFollowers < 0 ) {
        throw invalid_argument(to_string(initialFollowers));
    }

    this->name = name;
    this->numFollowers = initialFollowers;
    this->money = 0;
}

/*NEW constructor */
SNFollowers::SNFollowers(const BinSNFollowers &bSNF){
    this->name = bSNF.name;
    this->numFollowers = bSNF.numFollowers;
    this->money = bSNF.money;
}

BinSNFollowers SNFollowers::toBinSNFollowers()const{
    BinSNFollowers aux;
    strncpy(aux.name, this->name.c_str(), KMAXNAME-1);
    aux.name[KMAXNAME-1] = '\0';
    aux.numFollowers = this->numFollowers;
    aux.money = this->money;

    return aux;
}

/* 
 * Suma al número de seguidores el valor pasado por parámetro (que podría ser negativo si el influencer 
 * pierde seguidores). Después de la suma, si el valor del atributo numFollowers es negativo se debe poner a 
 * 0 (el número de seguidores no puede ser negativo, como mínimo debe ser 0).
 * */
void SNFollowers::addFollowers(int nf){
    this->numFollowers = this->numFollowers + nf;

    if (this->numFollowers <0) {
        this->numFollowers = 0;
    }
}

/*
 * Método que recalcula el número de seguidores (y la monetización
 * obtenida) en función de la valoración del evento (rating), que se pasa como parámetro, y la valora-
 * ción promedio de la red social. Si rating es negativo debe lanzarse la excepción invalid_argument
 * con rating (convertido a cadena con to_string). El cálculo se realiza de la siguiente manera:
 *
 * • Si la relación entre la valoración del evento y la de la red es mayor que 0,8, el número de
 * seguidores se incrementará en una cantidad que será el valor de dicha relación multiplicado
 * por el número actual de seguidores (tomando la parte entera de dicha operación). 
 *
 * • Si la relación es menor o igual que 0,8 se perderán seguidores y no se obtendrá dinero. La
 * cantidad de seguidores perdida será la resta de 0,9 menos la relación (p.ej. si la relación es
 * 0,7, la resta sería 0,2) multiplicada por el número de seguidores (tomando la parte entera).  
 * */
void SNFollowers::addEvent(double rating){
    double relat;
    int followersAdded;

    if (rating < 0) {
        throw invalid_argument(to_string(rating));
    }

    relat = rating/SNData::getAvgRating(this->name);

    if(relat > 0.8){ 
        followersAdded = this->numFollowers*relat;
        this->addFollowers(followersAdded);

        this->money = SNData::getAvgMonetizing(this->name)*followersAdded + this->money;

    }else {
        this->addFollowers(- (int) this->numFollowers*(0.9 - relat));
    }
}

/* 
 * Calcula la monetización que corresponde a la agencia, multiplicando la comisión pasada como 
 * parámetro por la cantidad de dinero obtenida hasta el momento, y la devuelve. Antes de finalizar 
 * pone la cantidad de dinero a 0 porque la agencia va a cobrar dicha comisión inmediatamente, y
 * debe resetear esa cantidad a 0 para que la próxima vez que se recolecte dinero no se cobre comisión 
 * sobre el dinero anterior por el que ya se ha cobrado (los influencers se darían cuenta). 
 * El valor de commission debe ser mayor que 0 y menor que 1, en caso contrario se lanzará la excepción 
 * invalid_argument (convirtiendo a cadena la dicho valor) sin hacer nada más, como en otros métodos.
 * */
double SNFollowers::collectCommission(double commission){
    double a;

    if (commission<=0 || commission>=1) {
        throw invalid_argument(to_string(commission));
    }

    a = commission * this->money;
    this->money = 0;
    return a;
}

std::string SNFollowers::getName() const{
    return this->name;
}

int SNFollowers::getNumFollowers() const{
    return this->numFollowers;
}

double SNFollowers::getMoney() const{
    return this->money;
}

std::ostream& operator<<(std::ostream &os, const SNFollowers &snf){
    os<<'['<<snf.getName()<<'|'<<snf.getNumFollowers()<<'|'<< snf.getMoney() <<']' ;
    return os;
}

