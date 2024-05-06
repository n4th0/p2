#include "SNData.h"
#include <stdexcept>
#include <string>

using namespace std;

std::vector<struct SocialNetworkData> SNData::sns;

/*
 * Añade al final del vector sns un nuevo registro con los datos de la nueva red social. 
 * Si ya existía una red con ese nombre, se lanza la excepción estándar invalid_argument pasándole 
 * como parámetro el nombre de la red.
 *
 * Los valores avgR y avgM deben ser mayores que 0 y menores que 1, en caso contrario se debe lanzar
 * la excepción invalid_argument pasándole como argumento el valor incorrecto convertido a cadena
 * con to_string, por ejemplo con to_string(avgM)
 *
 * */
void SNData::newSocialNetwork(string name, double avgR, double avgM){
    struct SocialNetworkData snd;

    if (checkSN(name)) {
        throw invalid_argument(name);
    }

    if ( avgR<0 || avgR>1 ) {
        throw invalid_argument(to_string(avgR));
    }

    if ( avgM<0 || avgM>1 ) {
        throw invalid_argument(to_string(avgM));
    }

    snd.name = name;
    snd.averageMonetizing = avgM;
    snd.averageRating = avgR;

    sns.push_back(snd);

}

/*
 * Busca en el vector sns una red social llamada name, y devuelve true
 * si la encuentra, y false en otro caso.
 * */
bool SNData::checkSN(std::string name){
    bool found = false;

    for(unsigned int i = 0; i<sns.size(); i++){
        if (sns[i].name == name) {
            found = true;
        }
    }

    return found;
}

/*
 * Devuelve la valoración promedio de la red social llamada
 * name, o 0.0 si no la encuentra.
 * */
double SNData::getAvgRating(std::string name){
    for(unsigned int i = 0; i<sns.size(); i++){
        if (sns[i].name == name) {
            return sns[i].averageRating;
        }
    }

    return 0.0;
}

/*
 * Devuelve la monetización media de la red social llamada
 * name, o 0.0 si no la encuentra.
 * */
double SNData::getAvgMonetizing(std::string name){
    for(unsigned int i = 0; i<sns.size(); i++){
        if (sns[i].name == name) {
            return sns[i].averageMonetizing;
        }
    }

    return 0.0;
}

