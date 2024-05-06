#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
using namespace std;
#define B_FLAG "-b"
#define S_FLAG "-s"

// 1 = > error file 
// 2 = > error arguments 
void errores(int error){
	switch(error){
		case 1:
			cout <<"ERROR: cannot open file" << endl;
			exit(1); // salida del programa 1 ya que es un error 
			break;
		case 2:
			cout <<"ERROR: wrong arguments" << endl;
			exit(1); // salida del programa 1 ya que es un error 
			break;
	}
}

void handlArgs(int argv, char ** argc){
	
	if(!(argv == 3 || argv == 5 )) {
		errores(2);
	}
	

	
	if(argv == 3){
		if(strcmp(argc[1], B_FLAG)!=0 ){
			errores(2);
		}

	}else if(argv == 5){
		if(strcmp(argc[1], B_FLAG)==0 ){
			if(strcmp(argc[3], S_FLAG)==0 ){

			}else{
				errores(2);
			}
		} else if(strcmp(argc[1], S_FLAG)==0 ){
			if(strcmp(argc[3], B_FLAG)==0 ){

			}else{
				errores(2);
			}
		}

	}




}


int main(int argv, char ** argc){
	cout << argv<< endl;
	handlArgs(argv, argc);

}

