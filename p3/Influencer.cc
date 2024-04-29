#include "SNData.h"
#include "Influencer.h"
#include "SNFollowers.h"
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

    if(!SNData::checkSN(snName)){
        try {
            SNFollowers seguidores(snName, nfollowers);
            this->followers.push_back(seguidores);

        } catch (Exception e) {
            if(e == EXCEPTION_UNKNOWN_SN){
                throw ERR_UNKNOWN_SN;
                return; // creo que esto no hace falta
            }
        }

    }else {
        this->addFollowers(snName, nfollowers);
    }

}

void Influencer::addEvent(int nsns, std::string sn[], double rat[]){

    for (unsigned int i = 0; this->followers.size(); i++) {
        for (int j = 0; j<nsns; j++) {
            if (sn[j] ==  this->followers[i].getName()) {

                this->followers[i].addFollowers(rat[j]);
            }
        }
    }

}

double Influencer::collectCommission(){
    double cant = 0;
    for (unsigned int i = 0; i < this->followers.size(); i++) {
        cant= cant + this->followers[i].collectCommission(this->commission);
    }

    return cant;

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

    for (unsigned int i = 0 ; i<inf.followers.size(); i++) {
        os << inf.followers[i];
    }

    return os;
}
