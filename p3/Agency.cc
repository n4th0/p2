#include "Agency.h"
#include <iostream>



Agency::Agency(std::string name, double initialMoney){
    // TODO terminar la funcion

}

Influencer Agency::seachInfluencer(std::string infName){
    // TODO terminar la funcion
}

void Agency::addInfluencer(std::string infName, double commission){
    // TODO terminar la funcion

}

void Agency::addFollowers(std::string infName, std::string snName, int nfollowers){
    // TODO terminar la funcion

}

void Agency::newEvent(std::vector<std::string> infNames, int nsns, std::string snNames[], double evtRatings[]){
    // TODO terminar la funcion

}

void Agency::deleteInfluencer(std::string infName){
    // TODO terminar la funcion

}

double Agency::collectCommissions(){
    // TODO terminar la funcion

}

std::string Agency::getName() const{
    return Agency::name;

}

double Agency::getMoney() const{
    return Agency::money;
}

std::ostream& operator<<(std::ostream &os, const Agency &ag){
    os << "Agency: " <<ag.getName() << " ["<<ag.getMoney()<<"]"<<std::endl;

    for (int i = 0; i<ag.influencers.size(); i++) {
        os << ag.influencers[i];
    
    }

    return os;
}
