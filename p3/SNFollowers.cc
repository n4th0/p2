
#include "SNFollowers.h"
// #include "SNData.h" (así es como accedo a la base de datos??) 
#include <string>
using namespace std;

SNFollowers::SNFollowers(std::string name, int initialFollowers){

    // TODO como carajos, como carajos accedo al struct SNData para obtener los que 
    // están duplicados?

    SNFollowers::name = name;


}

void SNFollowers::addFollowers(int nf){
    SNFollowers::numFollowers = SNFollowers::numFollowers + nf;

    if (SNFollowers::numFollowers <0) {
        SNFollowers::numFollowers = 0;
    }

}

void SNFollowers::addEvent(double rating){
    if (rating < 0) {
        throw exception(invalid_argument(to_string(rating)));
    }

    // TODO como accedo a la base de datos??

}

double SNFollowers::collectCommission(double commission){
    double a;

    if (commission<0 || commission>1) {
        throw exception(invalid_argument(to_string(commission)));
    }
    
    a = commission * SNFollowers::money;
    SNFollowers::money = 0;
    return a;
}

std::string SNFollowers::getName() const{
    return SNFollowers::name;

}

int SNFollowers::getNumFollowers() const{
    return SNFollowers::numFollowers;
}

double SNFollowers::getMoney() const{
    return SNFollowers::money;
}

std::ostream& operator<<(std::ostream &os, const SNFollowers &snf){
    os<<'['<<snf.getName()<<'|'<<snf.getNumFollowers()<<'|'<< snf.getMoney() <<']' ;
    return os;
}

