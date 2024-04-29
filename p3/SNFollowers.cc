
#include "SNData.h"
#include "SNFollowers.h"
#include "Util.h"
#include <stdexcept>
#include <string>
using namespace std;

SNFollowers::SNFollowers(std::string name, int initialFollowers){

    if(SNData::checkSN(name)){
        throw EXCEPTION_UNKNOWN_SN;
    }

    if (initialFollowers < 0 ) {
        throw invalid_argument(to_string(initialFollowers));
    }

    this->name = name;
    this->numFollowers = initialFollowers;
}

void SNFollowers::addFollowers(int nf){
    SNFollowers::numFollowers = SNFollowers::numFollowers + nf;

    if (SNFollowers::numFollowers <0) {
        SNFollowers::numFollowers = 0;
    }

}

void SNFollowers::addEvent(double rating){
    // TODO comprobar la función
    double relat;
    if (rating < 0) {
        throw invalid_argument(to_string(rating));
    }

    relat =rating/SNData::getAvgRating(this->name);

    if( relat > 0.8){ // 0.8 debería ser constante
        this->addFollowers((int) this->numFollowers*relat);

        // dudo mucho que se pueda hacer esto TODO (money stuff )
        this->money = this->money + ((int) this->numFollowers*relat);

    }else {
        this->addFollowers((int) this->numFollowers*(0.9 - relat));
    
    }


}

double SNFollowers::collectCommission(double commission){
    double a;

    if (commission<0 || commission>1) {
        throw invalid_argument(to_string(commission));
    }
    
    a = commission * SNFollowers::money;
    this->money = 0;
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

