#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#define OUTPUTFILE "aptos.txt"

using namespace std;

/*
 * 
 * */
struct empleado{
	char dni[100];
	char name[100];
	int salary;
	int year;
};

/*
 * error handle
 * 1 => error args 
 * 2 => error filename
 * 3 => error open file
 * */
void error(int a){
	switch(a){
		case 1:
			cout << "ERROR: wrong args"<< endl;
			exit(-1);
			break;
		case 2:
			cout << "ERROR: wrong filename"<< endl;
			exit(-1);
			break;
		case 3:
			cout << "ERROR: wrong open file "<< endl;
			exit(-1);
			break;
	}
}

void argHandle(int argc, char ** argv, string & filename, double & salary){
	if (argc != 3 && argc != 5){
		error(1);
	}
	string arg;
	
	for(int i = 1; i<argc; i++){
		arg = argv[i];
		if(arg == "-b"){
			if (filename != "") error(1);
			i++;
			if(i < argc)
				filename = argv[i];
			else
				error(1);
		} else if(arg == "-s"){
			i++;
			if(i < argc){
				salary = atof(argv[i]);
				if (salary < 10000 || salary >100000){
					error(1);
				}
			}
			else{
				error(1);
			}
		}else{
			error(1);
		}

	}
	if(filename.empty()){
		error(1);
	}

}
double computeAvg(const vector<struct empleado> &Empleados ){
	double avg= 0.0;
	for(unsigned int i = 0; i < Empleados.size(); i++){
		avg += Empleados[i].salary;
	}
	avg = avg/Empleados.size();

	// implicias = > sin perdidas de conversión  float / int  => float
	// explicitas => cast explicito (int) float / int => int

	return avg;
}

bool readInputFile( string & filename, vector<struct empleado> &Empleados ){
	ifstream fr(filename, ios::binary);

	if(!fr.is_open()){
		return false;
	}

	// forma de leer un binario  #include <fstream>
	empleado E;

	while(file.read((const char *)&E, sizeof(empleado))){
		empleados.push_back(empleado);
	}

	fr.close();
	return true;
}
bool writeOutputFile(const vector<struct empleado>&Empleados, avgSalary){
	ofstream fr(OUTPUTFILE);

	if(!fr.is_open()){
		return false;
	}


}

int main(int argc, char ** argv){
	string filename;
	double avgSalary = 0.0;
	argHandle(argc, argv, filename, avgSalary);
	vector<struct empleado> Empleados; 
	if(!readInputFile(filename, Empleados)){
		error(2);
	}

	if (avgSalary == 0.0){
		avgSalary = computeAvg(Empleados);
	}

	if(!writeOutputFile(Empleados, avgSalary)){
		error(3);
	}

}

