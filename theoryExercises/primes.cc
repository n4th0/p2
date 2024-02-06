
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

    if (argc>3) {
        cout << "Error: primes [-L] [-N n]"<<endl;
        return ERROR_TOO_MUCH_ARGS;
    }
    
    if(argc == 2) {
        if (strcmp(argv[1], NFLAG)==0) {
            printPrimes(DEFAULT);
        } else if (strcmp(argv[1],LFLAG)) {
            printPrimesN(DEFAULT);
        }

    }else if(argc==3){
        if (strcmp(argv[1],NFLAG)==0) {
            printPrimes(atoi(argv[2]));
        } else if (strcmp(argv[1],LFLAG)==0) {
            printPrimesN(atoi(argv[2]));
        }
    }

    cout << endl;

    return 0;
}

