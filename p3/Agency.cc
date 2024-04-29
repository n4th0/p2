#include "SNData.h"
#include "Agency.h"
#include "Influencer.h"
#include "Util.h"
#include <iostream>



Agency::Agency(std::string name, double initialMoney){
    this->name = name;
    this->money = initialMoney;
}

Influencer * Agency::seachInfluencer(std::string infName){

    bool found = false;
    int position = 0;
    for (unsigned int i = 0; i<this->influencers.size(); i++) {
        if (this->influencers[i].getName() == infName) {
            found = true;
            position = i;
        }
    }

    if (!found) {
        throw EXCEPTION_INFL_NOT_FOUND;
    }

    return  &this->influencers[position];
}

void Agency::addInfluencer(std::string infName, double commission){
    
    try {
        Influencer * inf = this->seachInfluencer(infName);
        inf->setCommission(commission);
        this->influencers.push_back(*inf);

    } catch (Exception e) {
        if (e == EXCEPTION_INFL_NOT_FOUND) {
            Util::error(ERR_DUPLICATED);
        }
        if (e == EXCEPTION_WRONG_COMMISSION) {
            Util::error(ERR_WRONG_COMMISSION);
        }
    }

}

void Agency::addFollowers(std::string infName, std::string snName, int nfollowers){

    try {
        Influencer *i = this->seachInfluencer(infName);
        i->addFollowers(snName, nfollowers);

    } catch (Exception e) {
        if (e == EXCEPTION_INFL_NOT_FOUND) {
            Util::error(ERR_NOT_FOUND);
            return;
        }
    }

}

void Agency::newEvent(std::vector<std::string> infNames, int nsns, std::string snNames[], double evtRatings[]){

    Influencer *inf;
    for (unsigned int i = 0; i<infNames.size(); i++) {
        // utilizar esto como if me parece criminal
        try {
            inf = this->seachInfluencer(infNames[i]);
            inf->addEvent(nsns, snNames, evtRatings);
        } catch (Exception e) {
            continue;
        }
    
    }

}

void Agency::deleteInfluencer(std::string infName){

    try {
        Influencer *inf = this->seachInfluencer(infName);
        this->money = this->money +inf->getCommission();

    } catch (Exception e) {
        if (e == EXCEPTION_INFL_NOT_FOUND) {
            Util::error(ERR_NOT_FOUND);
        }
    }



}

double Agency::collectCommissions(){
    // no se si tengo que poner las comisiones recolectadas a 0 (creo que no)

    double ret = 0.0;
    for (unsigned int i = 0; i<this->influencers.size(); i++) {
        ret = this->influencers[i].collectCommission() + ret;
    }
    return ret;

}

std::string Agency::getName() const{
    return Agency::name;

}

double Agency::getMoney() const{
    return Agency::money;
}

std::ostream& operator<<(std::ostream &os, const Agency &ag){
    os << "Agency: " <<ag.getName() << " ["<<ag.getMoney()<<"]"<<std::endl;

    for (unsigned int i = 0; i<ag.influencers.size(); i++) {
        os << ag.influencers[i];
    
    }

    return os;
}
