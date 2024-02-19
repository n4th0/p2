
#include <iostream>
#include <string.h>
using namespace std;

#define ERROR_TOO_MUCH_ARGS 1
#define DEFAULT 20
#define NFLAG "-N"
#define LFLAG "-L"

bool isPrime(int n){

    for (int i = 2; i<n; i++) {
        if (n%i==0) {
            return false;
        }
    }
    return true;
}

void printPrimes(int n){
    int count=0;
    for (int i = 1; count<n; i++) {
        if (isPrime(i)) {
            cout << i<< " ";
            count++;
        }
    }
}

void printPrimesN(int n){
    int count=0;
    for (int i = 1; count<n; i++) {
        if (isPrime(i)) {
            cout << i << endl;
            count++;
        }
    }
}

int main(int argc, char *argv[]){

    int indxN=0, indxL=0;
    for (int i = 0; i<argc-1; i++) {
        if (strcmp(argv[i],NFLAG)==0 ) {
            indxN=i;
            cout << indxN<<endl;
        }

        if (strcmp(argv[i],LFLAG)==0 ) {
            indxL=i;
            cout << indxL<<endl;
        }

    }
    
    if ((indxL-indxN)==1 && indxN!=0) {
        cerr << "error at the put the parameters"<<endl;
    }

    
    if(argc == 1) {
        if (indxN!=0) {
            printPrimes(DEFAULT);
        } else if (indxL!=0) {
            printPrimesN(DEFAULT);
        }

    }else if(argc==3){
        if (indxN!=0) {

            printPrimes(atoi(argv[indxN+1]));

        } else if (indxL!=0) {

            printPrimesN(atoi(argv[indxL+1]));
        }
    }
    cout << endl;

    return 0;
}

