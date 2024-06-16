#include "SNData.h"
#include "Util.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <fstream>
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

    if ( avgR <= 0 || avgR >= 1 ) {
        throw invalid_argument(to_string(avgR));
    }

    if ( avgM<=0 || avgM>=1 ) {
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
unsigned int SNData::getSocialNetworkNumber(){
    return sns.size();
}

void SNData::readFromCSV(std::string filename){
    int cont = 0;
    fstream fr;
    fr.open(filename, ios::in);
    string name, line, aux;
    double avR = 0.0;
    double avM = 0.0;

    if (!fr.is_open()) {
        Util::error(ERR_FILE);
        return;
    }


    while (getline(fr, line)) {
        if (line.empty()) 
            continue;
        cont++;

        if (line.find(SEPARATOR) == string::npos) {
            cout << "Error line "<< cont+1<<endl;
            continue;
        }
        name = line.substr(0, line.find(SEPARATOR));
        line.erase(0, line.find(SEPARATOR)+1);

        if (line.find(SEPARATOR) == string::npos) {
            cout << "Error line "<< cont+1<<endl;
            continue;
        }
        aux = line.substr(0, line.find(SEPARATOR));
        line.erase(0, line.find(SEPARATOR)+1);
        avR = atof(aux.c_str());

        avM = atof(line.c_str());

        try {
            newSocialNetwork(name, avR, avM);
        } catch (...) {
            cout << "Error line "<< cont+1<<endl;
        }
    }

    fr.close(); 
}

void SNData::writeToCSV(std::string filename){
    fstream fr;
    fr.open(filename, ios::in);

    if (!fr.is_open()) {
        Util::error(ERR_FILE);
        return;
    }

    for (unsigned i = 0; i<sns.size(); i++) {
        fr << sns[i].name <<SEPARATOR<< sns[i].averageRating <<SEPARATOR<< sns[i].averageMonetizing;
    }

    fr.close();
}




