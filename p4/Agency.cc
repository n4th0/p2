#include "SNData.h"
#include "Agency.h"
#include "Influencer.h"
#include "SNFollowers.h"
#include "Util.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;


Agency::Agency(std::string filename){
    fstream fr;
    fr.open(filename, ios::binary | ios::in);
    if (!fr.is_open()) {
        // mandar error
        Util::error(ERR_FILE);
        throw EXCEPTION_FILE;
    }
    BinAgency agencia;
    BinInfluencer influencer;
    BinSNFollowers follower;
    
    fr.read((char *)&agencia, sizeof(BinAgency));

    for (int i = 0; i<agencia.numInfluencers; i++) {

        fr.read((char *)&influencer, sizeof(BinInfluencer));
        Influencer influ(influencer);

        for (int j = 0; j< influencer.numFollowers; j++) {
            fr.read((char *)&follower, sizeof(BinSNFollowers));

            SNFollowers f(follower);
            influ.addFollowers(f);
        }

        this->influencers.push_back(influ);
    }

    fr.close();

    this->money = agencia.money;
    this->name = agencia.name;
}


unsigned int Agency::getNumberInfluencers()const{
    return influencers.size();
}

void Agency::saveData(std::string filename){
    fstream fr;
    fr.open(filename, ios::binary | ios::out);
    BinAgency agencia = this->toBinAgency();
    BinInfluencer influ;
    vector<SNFollowers> fols;
    BinSNFollowers fol;


    if (!fr.is_open()) {
        Util::error(ERR_FILE);
        return;
    }


    fr.write((char * )&agencia, sizeof(BinAgency));

    for (unsigned int i = 0; i<this->getNumberInfluencers(); i++) {

        influ = this->influencers[i].toBinInfluencer();

        fr.write((char * )&influ, sizeof(BinInfluencer));
        fols= influencers[i].getFollowers();
        for (unsigned j = 0; j<fols.size(); j++) {
            fol = fols[j].toBinSNFollowers();
            fr.write((char * )&fol, sizeof(BinSNFollowers));
        }

    }


    fr.close();
}

BinAgency Agency::toBinAgency()const{
    BinAgency aux;
    strncpy(aux.name, this->name.c_str(), KMAXNAME-1);
    aux.money = this->money;
    aux.numInfluencers = this->getNumberInfluencers();
    return aux;
}

Agency::Agency(std::string name, double initialMoney){
    this->name = name;
    this->money = initialMoney;
}

Influencer * Agency::searchInfluencer(std::string infName){

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

    return  & this->influencers[position];
}

void Agency::addInfluencer(std::string infName, double commission){

    try {
        searchInfluencer(infName);
        // si sigue es que lo ha encontrado (es decir, está mal)
        Util::error(ERR_DUPLICATED);
        return;

    } catch (Exception e) {

        if (e == EXCEPTION_INFL_NOT_FOUND) {

            Influencer inf(infName);
            try {
                inf.setCommission(commission);
                this->influencers.push_back(inf);

            } catch (Exception e) {
                if (e == EXCEPTION_WRONG_COMMISSION) {
                    Util::error(ERR_WRONG_COMMISSION);
                }
            }
        }
    }

}

void Agency::addFollowers(std::string infName, std::string snName, int nfollowers){

    try {
        Influencer *i = searchInfluencer(infName);
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

        try {
            inf = this->searchInfluencer(infNames[i]);
            inf->addEvent(nsns, snNames, evtRatings);
        } catch (Exception e) {
            continue;
        }
    
    }

}

void Agency::deleteInfluencer(std::string infName){
    int indice;

    try {
        Influencer *inf = this->searchInfluencer(infName);
        this->money = this->money + inf->collectCommission();

        for (unsigned int i = 0; i<this->influencers.size(); i++) {
            if (this->influencers[i].getName()== infName) {
                indice = i;
            }
        }

        this->influencers.erase(next(this->influencers.begin(), indice));

    } catch (Exception e) {
        if (e == EXCEPTION_INFL_NOT_FOUND) {
            Util::error(ERR_NOT_FOUND);
        }
    }



}

double Agency::collectCommissions(){
    double ret = 0.0;
    for (unsigned int i = 0; i<this->influencers.size(); i++) {
        ret = this->influencers[i].collectCommission() + ret;
    }
    this->money = this->money + ret;
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

    for (unsigned int i = 0; i<ag.influencers.size(); i++) 
        os << ag.influencers[i];

    os << std::endl;
    return os;
}
