#include <exception>
#include <iostream>
#include <string>
#include "SNData.h"

using namespace std;

void SNData::newSocialNetwork(string name, double avgR, double avgM){
    struct SocialNetworkData snd;

    if (checkSN(name)) {
        throw exception(invalid_argument(name));
    }

    if (avgR<0 || avgR>1) {
        throw exception(invalid_argument(to_string(avgR)));
    }

    if (avgM<0 || avgM>1) {
        throw exception(invalid_argument(to_string(avgM)));
    }

    snd.name= name;
    snd.averageMonetizing= avgM;
    snd.averageRating= avgR;

    SNData::sns.push_back(snd);


}

bool SNData::checkSN(std::string name){

    bool found = false;
    for(unsigned int i = 0; i<SNData::sns.size(); i++){
        if (SNData::sns[i].name == name) {
            found = true;
        }
    }
    return found;

}

double SNData::getAvgRating(std::string name){

    for(unsigned int i = 0; i<SNData::sns.size(); i++){
        if (SNData::sns[i].name == name) {
            return SNData::sns[i].averageRating;
        }
    }
    return 0.0;

}

double SNData::getAvgMonetizing(std::string name){

    for(unsigned int i = 0; i<SNData::sns.size(); i++){
        if (SNData::sns[i].name == name) {
            return SNData::sns[i].averageMonetizing;
        }
    }
    return 0.0;

}

