#include <iostream>
#include <vector>
using namespace std;

bool modulo(vector<int> prueba){
    int  algo = prueba.size();
    int num;

    for (int i = 0; i<algo; i++) {
        cout<<prueba[i]<< " ";
    }
    cout << endl;

    for (int i = 0; i<algo; i++) {
        for (int j = 0; j<algo-1; j++) {
            if (prueba[j]>prueba[j+1]) {
                num = prueba[j];
                prueba[j]=prueba[j+1];
                prueba[j+1]=num;
            }
        }
    }

    cout << endl;
    cout << endl;
    for (int i = 0; i<algo; i++) {
        cout<<prueba[i]<< " ";
    }
    cout << endl;
    cout << endl;

    for (int i = 0; i<algo-1; i++) {
        if ((prueba[i]-prueba[i+1])!=-1) {
            return false;
        }
    }
    return true;
}

int main(){

    cout<<modulo({7,6,4,5,2,2,1});


    return 0;
}

