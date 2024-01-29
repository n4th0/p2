#include <iostream>
using namespace std;

// exercise 1
bool multiple(int a, int b){
    return (b%a==0)||(a%b==0);
}

// exercise 2
int printN(int number){
    if (number<4) {
        cout << "ERROR" << endl;
        // could be 1 to say that have been an error
        return 0;
    }
    cout << "*";
    for (int i = 0 ; i<number-2; i++) {
        cout << " ";
    }

    for (int i = 0; i<number-2; i++) {
        for (int j = 0; j<number-1; j++) {


        
        }
    }


    return 4+(number-2)*3;
}


