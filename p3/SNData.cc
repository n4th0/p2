#include "SNData.h"
#include <stdexcept>
#include <string>

using namespace std;

void SNData::newSocialNetwork(string name, double avgR, double avgM){
    struct SocialNetworkData snd;

    if (checkSN(name)) {
        throw invalid_argument(name);
    }

    if (avgR<0 || avgR>1) {
        throw invalid_argument(to_string(avgR));
    }

    if (avgM<0 || avgM>1) {
        throw invalid_argument(to_string(avgM));
    }

    snd.name = name;
    snd.averageMonetizing = avgM;
    snd.averageRating = avgR;

    sns.push_back(snd);

}

bool SNData::checkSN(std::string name){
    bool found = false;
    // std::cout << "llego aqui fn2 1"<< std::endl;
    for(unsigned int i = 0; i<sns.size(); i++){
        if (sns[i].name == name) {
            // std::cout << "llego aqui fn2 2"<< std::endl;
            found = true;
        }
    }
    // std::cout << "llego aqui fn2 3"<< std::endl;
    return found;

}

double SNData::getAvgRating(std::string name){
    for(unsigned int i = 0; i<sns.size(); i++){
        if (sns[i].name == name) {
            return sns[i].averageRating;
        }
    }
    return 0.0;

}

double SNData::getAvgMonetizing(std::string name){
    for(unsigned int i = 0; i<sns.size(); i++){
        if (sns[i].name == name) {
            return sns[i].averageMonetizing;
        }
    }
    return 0.0;

}

