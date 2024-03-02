// Programación 2 - Práctica 1
// DNI: 48727425 Q
// Nombre: NATHAN RODRIGUEZ MOYSES

#include <iostream>
#include <string>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <stdlib.h>


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
struct Date askDate(){
    Date a;
    string s;
    int pos;
    cout<< "Enter date (year-month-day): ";
    getline(cin, s);

    if (s.empty()) {
        a.day=0;
        a.year=0;
        a.month=0;
        return a;
    }

    a.year=atoi(s.substr(0,4).c_str());
    s.erase(0,5);
    pos= s.find("-");
    a.month = atoi(s.substr(0,pos).c_str());
    s.erase(0, pos+1);
    a.day = atoi(s.c_str());
    return a;
}

vector<AcademicYear> deleteTeacher(vector<AcademicYear> years){
    string s;
    bool name=false;
    int indx_teach=-1, indx_year=-1;

    while (!name) {
        cout << "Enter teacher name: ";
        getline(cin, s);
        if (s.empty()) {
            error(ERR_EMPTY);
            return years;
        }
        for (unsigned int i = 0; i< years.size(); i++) {
            for (unsigned int j = 0; j< years[i].listTeachers.size(); j++) {
                if (s==years[i].listTeachers[j].name) {
                    name=true;
                    indx_teach=j;
                    indx_year=i;
                }
            }
        }
    }

    years[indx_year].listTeachers.erase(next(years[indx_year].listTeachers.begin(), indx_teach));
    return years;

}


vector<AcademicYear> addTeacher(vector<AcademicYear> years){
    int id, indx;
    string s;
    string prueba;
    string rating;
    bool exist= false;
    bool duplicated= false;
    Teacher a;

    cout <<"Enter academic year: ";
    getline(cin, prueba);

    if (prueba.empty()) {
        error(ERR_EMPTY);
        return years;
    }

    id = stoi(prueba);

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

    cout <<"Enter teacher name: ";
    getline(cin, a.name);

    if(a.name.empty()){
        error(ERR_EMPTY);
        return years;
    }

    for (unsigned int i = 0; i < years[indx].listTeachers.size() ; i++) {
        if (a.name==years[indx].listTeachers[i].name) {
            duplicated= true;
            error(ERR_DUPLICATED);
        }
    }

    while(duplicated){
        duplicated=false;

        cout <<"Enter teacher name: ";
        getline(cin, a.name);

        if(a.name.empty()){
            error(ERR_EMPTY);
            return years;
        }

        for (unsigned int i = 0; i < years[indx].listTeachers.size() ; i++) {
            if (a.name==years[indx].listTeachers[i].name) {
                duplicated= true;
                error(ERR_DUPLICATED);
            }
        }

    }


    // falta añadir el error empty string
    cout <<"Enter nickname: ";
    getline(cin, a.nickname);

    cout <<"Enter subject: ";

    getline(cin, s);

    if (s.empty()) {
        error(ERR_EMPTY);
        return years;
    }

    strncpy(a.subject, s.c_str(), 50);

    
    cout <<"Enter rating: ";
    getline(cin,rating);

    if (rating.empty()) {
        a.rating = 0;
        years[indx].listTeachers.push_back(a);
        return years;
    }

    while (stoi(rating)<1 || stoi(rating)>5) {
        error(ERR_DUPLICATED);

        cout <<"Enter rating: ";
        getline(cin,rating);
        if (rating.empty()) {
            a.rating = 0;
            years[indx].listTeachers.push_back(a);
            return years;
        }
    }

    a.rating=stoi(rating);
    years[indx].listTeachers.push_back(a);
    return years;


}

vector<AcademicYear> deleteAcademicYear(vector<AcademicYear> years){
    string year;
    int y=0, year_index=-1;
    bool ye=false;

    while (!ye) {
        cout << "Enter academic year: ";
        getline(cin,year);

        if (year.empty()) {
            error(ERR_EMPTY);
            return years;
        }

        y= stoi(year);

        for (unsigned i = 0; i<years.size(); i++) {
            if(years[i].id==y){
                year_index=i;
            }
        }

        if (year_index==-1) {
            error(ERR_NOT_EXIST);
        }else {
            ye=true;
        }
    }
    years.erase(next(years.begin(), year_index));
    return years;
    

}


vector<AcademicYear> addPhrase(vector<AcademicYear> years){
    string name, phrase;
    char aux[10];
    bool n=false;
    int indx_year=-1, indx_teach=-1;

    while (!n) {
        cout << "Enter teacher name: ";
        getline(cin,name);

        if(name.empty()){
            error(ERR_EMPTY);
            return years;
        }

        for (unsigned int j = 0; j<years.size(); j++) {
            for(unsigned int i = 0; i<years[j].listTeachers.size(); i++){
                if (name==years[j].listTeachers[i].name) {
                    indx_teach= i;
                    indx_year= j;
                    n=true;
                }
            }
        }
        // if one of them are -1 has been an error  
        if (indx_year==-1 || indx_teach==-1) {
            error(ERR_NOT_EXIST);
            return years;
        }
    }

    cout << "Enter phrase: ";
    getline(cin, phrase);
    if (phrase.empty()) {
        error(ERR_EMPTY);
        return years;
    }

    Phrase a;
    a.text=phrase;
    a.date = askDate();


    cout << "Enter rating: ";
    cin.getline(aux, 10);

    if(strlen(aux)==0){
        a.rating=0;
    }else {
        while(atoi(aux)<1 || atoi(aux)>10){
            aux[0]='1';
            if (atoi(aux)==0) {
                cout << "ha habido un error"<<endl;
                cout << "Enter a rating: ";
                cin.getline(aux, 10);
            }else {
            error(ERR_RATING);
            cout << "Enter a rating: ";
            cin.getline(aux, 10);
                if (atoi(aux)==0) {
                    cout << "ha habido un error"<<endl;
                }
            }
        }
    }
    a.rating=atoi(aux);
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

            cout << ": " << years[indx_year].listTeachers[indx_teach].listPhrases[i].text<< endl;
        
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
    string s;

    string prueba;
    bool dup=false;
    cout << "Enter academic year: ";
    getline(cin,prueba);

    if (prueba.empty()) {
        error(ERR_EMPTY);
        return years;
    }


    id = stoi(prueba);

    for (auto itr : years) {
        if (itr.id == id) {
            error(ERR_DUPLICATED);
            dup = true;
        }
    }
    
    while (dup) {
        dup = false;
        cout << "Enter academic year: ";
        getline(cin, prueba);

        if (prueba.empty()) {
            error(ERR_EMPTY);
            return years;
        }


        id = stoi(prueba);
        // odio esta forma de recorrer vectores
        for (auto itr : years) {
            if (itr.id == id) {
                error(ERR_DUPLICATED);
                dup = true;
            }
        }
    }

    AcademicYear a;
    a.id = id;
    years.push_back(a);
    return years;

}
void summary(vector<AcademicYear> years){
    int aux, indx=years.size()-1;

    while (years.size()!=0) {
        aux=years[years.size()-1].id;
        for (unsigned int i = 0; i<years.size(); i++) {
            if (years[i].id>aux) {
                aux = years[i].id;
                indx= i;
            }
        }

        if (years[indx].listTeachers.size()!=0) {

            cout << "Academic year: " << years[indx].id<<endl;
            // vivan los fors
            for (unsigned int j = 0; j<years[indx].listTeachers.size(); j++) {
                for (unsigned int k = 0; k<years[indx].listTeachers[j].listPhrases.size(); k++) {
                    // una vez más, formato odioso
                    cout << years[indx].listTeachers[j].name;

                    if (years[indx].listTeachers[j].listPhrases[k].rating==0) {
                         cout << " - " << years[indx].listTeachers[j].listPhrases[k].text<<endl;
                    
                    }else {

                        cout << " - " << years[indx].listTeachers[j].listPhrases[k].rating 
                            << " - " << years[indx].listTeachers[j].listPhrases[k].text<<endl;
                    }
                }
            }

        }

        years.erase(next(years.begin(), indx));
    }

}

// Función principal. Tendrás que añadir más código tuyo
int main(){
    char option;
    vector<AcademicYear> years;
    
    do{
        showMenu();
        cin >> option;
        cin.get(); // Para evitar que el salto de línea se quede en el buffer de teclado y luego pueda dar problemas si usas "getline"
        //cout << "\e[1;1H\e[2J";
        switch(option){
            case '1': // Llamar a la función "addAcademicYear" para crear un nuevo curso
                    years = addAcademicYear(years);
                break;
            case '2': // Llamar a la función "deleteAcademicYear" para eliminar un curso
                    years = deleteAcademicYear(years);
                break;
            case '3': // Llamar a la función "addTeacher" para crear un nuevo profesor
                    years = addTeacher(years);
                break;
            case '4': // Llamar a la función "deleteTeacher" parar eliminar un profesor
                      years = deleteTeacher(years);
                break;
            case '5': // Llamar a la función "showTeacher" para mostrar la información del profesor
                    showTeacher(years);
                break;
            case '6': // Llamar a la función "addPhrase" para añadir una nueva frase
                      years= addPhrase(years);
                break;
            case '7': // Llamar a la función "summary" para mostrar un resumen de las frases por curso
                      summary(years);
                break;
            case 'q': break;
            default: error(ERR_OPTION);
        }
    }while(option!='q');
}
