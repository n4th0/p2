// Programación 2 - Práctica 1
// DNI: 48727425 Q
// Nombre: NATHAN RODRIGUEZ MOYSES
#include <cstdio>
#include <iostream>
#include <system_error>
#include <type_traits>
#include <vector>
#include <stdlib.h>
#include <string.h>


using namespace std;

const int MAXSUBJECT=50;

// Registro para las fechas
struct Date{
    int day;
    int month;
    int year;
};

// Registro para las frases épicas
struct Phrase{
    string text;
    Date date;
    int rating;
};

// Registro para los profesores
struct Teacher{
    string name;
    string nickname;
    char subject[MAXSUBJECT];
    int rating;
    vector<Phrase> listPhrases;
};

// Registro para los cursos
struct AcademicYear{
    int id;
    vector<Teacher> listTeachers;
};

// Tipos de error posibles
enum Error{
    ERR_OPTION,
    ERR_EMPTY,
    ERR_DUPLICATED,
    ERR_NOT_EXIST,
    ERR_RATING
};

/* Función que muestra los mensajes de error
e: tipo de error a mostrar
return: nada
*/
void error(Error e){
    switch(e){
        case ERR_OPTION: cout << "ERROR: wrong option" << endl;
            break;
        case ERR_EMPTY: cout << "ERROR: empty string" << endl;
            break;
        case ERR_DUPLICATED: cout << "ERROR: duplicated value" << endl;
            break;
        case ERR_NOT_EXIST: cout << "ERROR: value does not exist" << endl;
            break;
        case ERR_RATING: cout << "ERROR: number out of range" << endl;
    }
}


/* Función que muestra el menú de opciones
return: nada
*/
void showMenu(){
    cout << "1- Add academic year" << endl
         << "2- Delete academic year" << endl
         << "3- Add teacher" << endl
         << "4- Delete teacher" << endl
         << "5- Show teacher" << endl
         << "6- Add phrase" << endl
         << "7- Summary" << endl
         << "q- Quit" << endl
         << "Option: ";
}

vector<AcademicYear> addTeacher(vector<AcademicYear> years){
    int id, indx;
    char prueba[10];
    bool exist= false;

    cout <<"Enter academic year: ";
    cin.getline(prueba, 10);

    if (strlen(prueba)==0) {
        error(ERR_EMPTY);
        return years;
    }

    if (atoi(prueba)==0) {
        cout << "bad input"<<endl;
        return years;
    }

    // esto es solo una idea
    id = atoi(prueba);

    // falta chequear que no sea una empty string
    for (unsigned int i = 0; i < years.size() ; i++) {
        if (years[i].id==id) {
            exist= true;
            indx = i;
        }
    }

    if(!exist){
        error(ERR_NOT_EXIST);
        return years;
    }

    Teacher a;
    cout <<"Enter teacher name: ";
    cin>>a.name;
    if (a.name.empty()) {
        error(ERR_EMPTY);
        return years;
    }

    for (unsigned int i = 0; i < years[indx].listTeachers.size() ; i++) {
        if (a.name==years[indx].listTeachers[i].name) {
            error(ERR_DUPLICATED);
            return years;
        }
    }

    // falta añadir el error empty string
    cout <<"Enter nickname: ";
    cin>>a.nickname;
    cout <<"Enter subject: ";
    cin>>a.subject;
    cout <<"Enter rating: ";
    cin>>a.rating;

    years[indx].listTeachers.push_back(a);
    return years;

}

vector<AcademicYear> addPhrase(vector<AcademicYear> years){
    string name, phrase;
    char aux[10];
    bool y=false,m=false,d=false;
    int indx_year=-1, indx_teach=-1;
    cout << "Enter teacher name: "<< endl;
    getline(cin,name);

    // tiene que ser un bucle while TODO
    if(name.empty()){
        error(ERR_EMPTY);
        return years;
    }

    for (unsigned int j = 0; j<years.size(); j++) {
        for(unsigned int i = 0; i<years[j].listTeachers.size(); i++){
            if (name==years[j].listTeachers[i].name) {
                indx_teach= i;
                indx_year= j;
            }
        }
    }
    // if one of them are -1 has been an error  
    if (indx_year==-1 || indx_teach==-1) {
        error(ERR_NOT_EXIST);
        return years;
    }

    cout << "Enter phrase: "<< endl;
    getline(cin, phrase);
    if (phrase.empty()) {
        error(ERR_EMPTY);
        return years;
    }

    Phrase a;
    a.text=phrase;

    while (!y) {
        cout << "Enter date (year-month-day):";
        cin.getline(aux,10);
        if (strlen(aux)==0) {
            a.date.year=0;
        }else  {
            if (atoi(aux)==0) {
                cout << "ha habido un error"<<endl;
            }else {
                a.date.year=atoi(aux);
                y=true;
            }
        }
    }
    while (!m) {
        cout << "Enter date (year-month-day):";
        cin.getline(aux,10);
        if (strlen(aux)==0) {
            a.date.year=0;
        }else  {
            if (atoi(aux)==0) {
                cout << "ha habido un error"<<endl;
            }else {
                a.date.month=atoi(aux);
                m=true;
            }
        }
    }

    while (!d) {
        cout << "Enter date (year-month-day):";
        cin.getline(aux,10);
        if (strlen(aux)==0) {
            a.date.year=0;
        }else  {
            if (atoi(aux)==0) {
                cout << "ha habido un error"<<endl;
            }else {
                a.date.day=atoi(aux);
                d=true;
            }
        }
    }

    cout << "Enter a rating: "<<endl;
    cin.getline(aux, 2);

    if(strlen(aux)==0){
        a.rating=0;
    }else {
        if (atoi(aux)==0) {
            cout << "ha habido un error"<<endl;
        }else {
            while(atoi(aux)<1 || atoi(aux)>10){
                error(ERR_RATING);
                cout << "Enter a rating: "<<endl;
                cin.getline(aux, 2);
                if (atoi(aux)==0) {
                    cout << "ha habido un error"<<endl;
                }
            }
        }
    }



    


    years[indx_year].listTeachers[indx_teach].listPhrases.push_back(a);
    return years;
}

void showTeacher(vector<AcademicYear> years){
    int indx_teach=-3;
    int indx_year=-3;
    string name_prov;
    cout<< "Enter teacher name: ";
    getline(cin, name_prov);

    if (name_prov.empty()) {
        error(ERR_EMPTY);
        return;
    }

    for (unsigned int j = 0; j<years.size(); j++) {
        for(unsigned int i = 0; i<years[j].listTeachers.size(); i++){
            if (name_prov==years[j].listTeachers[i].name) {
                indx_teach= i;
                indx_year= j;
            }
        }
    }

    if (indx_teach==-3 || indx_year==-3) {
        error(ERR_NOT_EXIST);
        return;
    }
    cout << "Academic year: "<< years[indx_year].id<< endl;
    cout << "Name: "<< years[indx_year].listTeachers[indx_teach].name<< endl;
    cout << "Nickname: "<< years[indx_year].listTeachers[indx_teach].nickname<< endl;
    cout << "Subject: "<< years[indx_year].listTeachers[indx_teach].subject<< endl;
    cout << "Rating: "; for(int i = 0; i<years[indx_year].listTeachers[indx_teach].rating; i++){cout<<"*";} cout << endl;
    // este formato es un dolor de cabeza (debe haber alguna forma muchísmo mejor de hacerlo)
    for (unsigned int i = 0; i<years[indx_year].listTeachers[indx_teach].listPhrases.size(); i++) {
        cout<<"Phrase "<<i+1 ;
        if (years[indx_year].listTeachers[indx_teach].listPhrases[i].date.year==0 && years[indx_year].listTeachers[indx_teach].listPhrases[i].rating==0) {

            cout << " : " << years[indx_year].listTeachers[indx_teach].listPhrases[i].text<< endl;
        
        }else if (years[indx_year].listTeachers[indx_teach].listPhrases[i].date.year==0) {

            cout << " ["<<
                years[indx_year].listTeachers[indx_teach].listPhrases[i].rating
                << "]: " << years[indx_year].listTeachers[indx_teach].listPhrases[i].text<< endl;
        
        }else if (years[indx_year].listTeachers[indx_teach].listPhrases[i].date.year!=0 && years[indx_year].listTeachers[indx_teach].listPhrases[i].rating!=0) {

            cout << " ("<< years[indx_year].listTeachers[indx_teach].listPhrases[i].date.year<< "-" << years[indx_year].listTeachers[indx_teach].listPhrases[i].date.month<<"-"
                << years[indx_year].listTeachers[indx_teach].listPhrases[i].date.day<<") ["<<
                years[indx_year].listTeachers[indx_teach].listPhrases[i].rating
                << "]: " << years[indx_year].listTeachers[indx_teach].listPhrases[i].text<< endl;
        
            // podría ser solo el else pero me fio menos que de mi autocontrol para no asaltar la nevera a las 3 de la mañana 
        }else if (years[indx_year].listTeachers[indx_teach].listPhrases[i].date.year!=0 && years[indx_year].listTeachers[indx_teach].listPhrases[i].rating==0) {
        
            cout << " ("<< years[indx_year].listTeachers[indx_teach].listPhrases[i].date.year<< "-" << years[indx_year].listTeachers[indx_teach].listPhrases[i].date.month<<"-"
                << years[indx_year].listTeachers[indx_teach].listPhrases[i].date.day<<"): "<< years[indx_year].listTeachers[indx_teach].listPhrases[i].text<< endl;
        
        }
    }
}

vector<AcademicYear> addAcademicYear(vector<AcademicYear> years){
    int id;
    char prueba[10];
    cout << "Enter academic year: ";
    cin.getline(prueba, 10);

    if (strlen(prueba)==0) {
        error(ERR_EMPTY);
        return years;
    }

    if(atoi(prueba)==0){
        cout << "bad id, try it again"<<endl;
        return years;
    }
    id = atoi(prueba);
    
    // odio esta forma de recorrer vectores
    for (auto itr : years) {
        if (itr.id == id) {
            error(ERR_DUPLICATED);
            return years;
        }
    }

    AcademicYear a;
    a.id = id;
    years.push_back(a);
    return years;

}

// Función principal. Tendrás que añadir más código tuyo
int main(){
    char option;
    vector<AcademicYear> years;
    
    do{
        showMenu();
        cin >> option;
        cin.get(); // Para evitar que el salto de línea se quede en el buffer de teclado y luego pueda dar problemas si usas "getline"
        cout << "\e[1;1H\e[2J";
        switch(option){
            case '1': // Llamar a la función "addAcademicYear" para crear un nuevo curso
                    years = addAcademicYear(years);
                break;
            case '2': // Llamar a la función "deleteAcademicYear" para eliminar un curso
                break;
            case '3': // Llamar a la función "addTeacher" para crear un nuevo profesor
                    years = addTeacher(years);
                break;
            case '4': // Llamar a la función "deleteTeacher" parar eliminar un profesor
                break;
            case '5': // Llamar a la función "showTeacher" para mostrar la información del profesor
                      showTeacher(years);
                break;
            case '6': // Llamar a la función "addPhrase" para añadir una nueva frase
                break;
            case '7': // Llamar a la función "summary" para mostrar un resumen de las frases por curso
                break;
            case 'q': break;
            default: error(ERR_OPTION);
        }
    }while(option!='q');
}
