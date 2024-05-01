
#include "SNData.h"
#include "SNFollowers.h"
#include "Util.h"
#include <stdexcept>
#include <string>
using namespace std;

SNFollowers::SNFollowers(std::string name, int initialFollowers){
    if(!SNData::checkSN(name)){
        throw EXCEPTION_UNKNOWN_SN;
    }

    if (initialFollowers < 0 ) {
        throw invalid_argument(to_string(initialFollowers));
    }

    this->name = name;
    this->numFollowers = initialFollowers;
    this->money = 0.0;
}

void SNFollowers::addFollowers(int nf){
    this->numFollowers = this->numFollowers + nf;

    if (this->numFollowers <0) {
        this->numFollowers = 0;
    }

}

void SNFollowers::addEvent(double rating){
    double relat;
    int followersAdded;

    if (rating < 0) {
        throw invalid_argument(to_string(rating));
    }

    relat = rating/SNData::getAvgRating(this->name);

    if( relat > 0.8){ // 0.8 debería ser constante
        
        followersAdded = this->numFollowers*relat;
        this->addFollowers(followersAdded);

        this->money = SNData::getAvgMonetizing(this->name)*followersAdded + this->money;

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

