#include <iostream>
#include <string.h>
using namespace std;

// exercise 1
bool multiple(int a, int b){
    return (b%a==0)||(a%b==0);
}

// exercise 2
int printN(int number){
    // cheking if is less than 4
    if (number<4) {
        cout << "ERROR" << endl;
        // could be 1 to say that have been an error
        return 0;
    }

    for (int i = 0; i<number; i++) {
        for (int j = 0; j<number; j++) {
            if (j==0 || j == number-1) {
                cout <<"*";
            }else if (j==i) {
                cout <<"*";
            }else {
                cout <<" ";
            }
        }
        cout << endl;
    }

    return 4+(number-2)*3;
}

// exercise 3
bool isPrime(int p){

    for (int i = 2; i<p; i++) {
        if (p%i==0) {
            return false;
        }
    }
    return true;
}

int firstPrimes(int n){
    int auxiliar=0;
    int count=2;
    int sumatorio=0;

    while (auxiliar!=n) {
        if (isPrime(count)) {
            cout<< count;
            cout << " ";
            sumatorio = sumatorio + count;
            auxiliar++;
        }
        count++;
   }
    return sumatorio;
}

// exercise 4
// i fixed the error that speend to much time to calculate big numbers
void Goldbach(int n, int &p1, int &p2){
    int aux;

    for (int i = 2; i<n; i++) {
        for (int j = 2; j<n; j++) {
            if (isPrime(i) && isPrime(j) && j+i==n) {
                p1 = i;
                p2 = j;
//               if (p1>p2) {
//                   aux = p1;
//                   p1 = p2;
//                   p2 = aux;
//               }
                return;
                }
        }
    }

}


// exercise 5 

bool search(int v[], const int TAMVECTOR, int n){
    int aux = 0;
    for (int i = 0; i<TAMVECTOR; i++) {
        if (v[i]==n) {
            aux++;
        }
    }
    return aux!=0;
}

int position(int v[], const int TAMVECTOR, int n){
    for (int i = 0; i<TAMVECTOR; i++) {
        if (v[i]==n) {
            return i;
        }
    }
    return -1;
}

int count(int v[], const int TAMVECTOR, int n){
    int aux = 0;
    for (int i = 0; i<TAMVECTOR; i++) {
        if (v[i]==n) {
            aux++;
        }
    }
    return aux;
}

// exercise 5 
// el enunciado no concuerda con los tests, dice que tiene que retornar
// la posicion pero en los test devuelve el número, rarete (solo en el apartado a)

int minOdds(int v[], const int TAMVECTOR){
    int aux = v[0];

    for (int i = 0; i<TAMVECTOR; i++) {
        if((v[i]%2)!=0 && v[i]<aux){
            aux = v[i];
        }
    }

    if (aux%2!=0) {
        return aux;
    }else {
        return -1;
    }
}

int posMaxMultFive(int v[], const int TAMVECTOR){
    int aux = -1;

    for (int i = 0; i<TAMVECTOR; i++) {
        if((v[i]%5)==0 && v[i]>aux){
            aux = v[i];
        }
    }
    if (aux>0) {
        return position(v, TAMVECTOR, aux);
    }else {
        // could be aux too
        return -1;
    }
}

void deleteChar(char str[], char c){
    int lenght = strlen(str);

    for (int i = 0; i<lenght; i++) {
        if (c == str[i]) {
            for (int j = i; j<lenght-1; j++) {
                str[j] = str[j+1];
                str[j+1] = '\0';
            }
        }
    }
}


