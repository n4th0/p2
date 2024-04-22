#include "Influencer.h"
#include "Util.h"
#include <iostream>
#include <string>


Influencer::Influencer(std::string name){
    Influencer::name = name;
    Influencer::commission = 0.1;
}

void Influencer::setCommission(double commission){
    if (commission>0 && commission<0.8) {
        Influencer::commission = commission;
    } else {
        throw ERR_WRONG_COMMISSION;
    }

}

void Influencer::addFollowers(std::string snName, int nfollowers){
    // TODO terminar la funcion


}

void Influencer::addEvent(int nsns, std::string * sn, double * rat){
    // TODO terminar la funcion

}

double Influencer::collectCommission(){
    // TODO terminar la funcion

}

std::string Influencer::getName() const{
    return Influencer::name;
}

std::vector<SNFollowers> Influencer::getFollowers() const{
    return Influencer::followers;
}

double Influencer::getCommission() const{
    return Influencer::commission;
}

std::ostream & operator<<(std::ostream &os, const Influencer &inf){

    os << "Influencer: "<< inf.getName() << " ("<< 
        inf.getCommission()<<")"<<std::endl;

    for (int i = 0 ; i<inf.followers.size(); i++) {
        os << inf.followers[i];
    }

    return os;
}
