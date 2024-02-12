#include <iostream>
#include <string.h>
using namespace std;

struct nodo{
    char nombre;
    int vecinos;
    int array_pos;
    char conexiones[3];
};

bool distintasConexiones(char n1[], char n2[], int nV1, int nV2){
    for (int i = 0; i<nV1; i++) {
        for (int j = 0; j<nV1; j++) {
            if (n1[i]==n2[j]) {
                return false;
            }
        }
    }
    return true;
}
bool IsInString(char str[], char b){
    int a = strlen(str);
    for (int i = 0; i<a; i++) {
        if (str[i]==b) {
            return true;
        }
    }
    return false;
}

bool isBipartite(struct nodo nodos[], int size){
    char cadenaDerecha[10];
    char cadenaIzquierda[10];
    int indexD= 0, indexI=1;

    cadenaIzquierda[0]='a';
    for (int i = 0; i<size; i++) {
        if (IsInString(cadenaIzquierda, nodos[i].nombre)) {
            cadenaDerecha[indexD]=  nodos[i].conexiones[0];
            cadenaDerecha[indexD+1]=  nodos[i].conexiones[1];
            indexD=indexD+2;

        }else if (IsInString(cadenaDerecha,nodos[i].nombre )) {

            cadenaIzquierda[indexI]=  nodos[i].conexiones[0];
            cadenaIzquierda[indexI+1]=  nodos[i].conexiones[1];
            indexI=indexI+2;

        }else {

        }
    }

    cout <<"grafos a la izquierda: ";
        cout<<cadenaIzquierda;
    cout<<endl;
    cout <<"grafos a la derecha: ";
        cout<<cadenaDerecha;
    cout<<endl;

     
    return false;
}


int main(){
    struct nodo nodos[4];

    nodos[0].nombre='a';
    nodos[0].vecinos=2;
    nodos[0].array_pos=0;
    strcpy(nodos[0].conexiones, "bc");
    cout << nodos[0].conexiones<<endl;

    nodos[1].nombre='b';
    nodos[1].vecinos=2;
    nodos[0].array_pos=1;
    strcpy(nodos[1].conexiones, "ad");
    cout << nodos[1].conexiones<<endl;

    nodos[2].nombre='c';
    nodos[2].vecinos=2;
    nodos[0].array_pos=2;
    strcpy(nodos[2].conexiones, "ad");
    cout << nodos[2].conexiones<<endl;

    nodos[3].nombre='d';
    nodos[3].vecinos=4;
    nodos[0].array_pos=3;
    strcpy(nodos[3].conexiones, "bc");
    cout << nodos[3].conexiones<<endl;

    isBipartite(nodos, 4);




    return 0;
}

