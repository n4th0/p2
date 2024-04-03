#include <iostream>
#include <cctype>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <string>

using namespace std;

#define TEACHERFILE "teachers.bin"
#define FFLAG "-f"
#define SFLAG "-s"

const int KMAXNAME = 50;
const int KMAXPASSWORD = 5;


// registro para las preguntas
struct question{
    unsigned int id;
    unsigned int unit;
    string question;
    string answer;
};

// registro para los profesores
struct teacher{
    char name[KMAXNAME];
    char password[KMAXPASSWORD];
    unsigned int answered;
};

// registro para la base de datos
struct database{
    unsigned int nextid;
    vector<question> questions;
    vector<teacher> teachers;
};

// Tipos de errores posibles
enum Error {
    ERR_OPTION,
    ERR_EMPTY,
    ERR_UNIT,
    ERR_CHAR,
    ERR_FILE,
    ERR_NAME,
    ERR_DUPLICATED,
    ERR_PASSWORD,
    ERR_NO_QUESTIONS,
    ERR_ID,
    ERR_ARGS
};

/* Función que muestra los mensajes de error
e: tipo de error a mostrar
return: nada
*/
void error(Error e){
    switch (e){
        case ERR_OPTION:
            cout << "ERROR: wrong option" << endl;
            break;
        case ERR_EMPTY:
            cout << "ERROR: empty string" << endl;
            break;
        case ERR_UNIT:
            cout << "ERROR: wrong unit" << endl;
            break;
        case ERR_CHAR:
            cout << "ERROR: wrong char" << endl;
            break;
        case ERR_FILE:
            cout << "ERROR: cannot open file" << endl;
            break;
        case ERR_NAME:
            cout << "ERROR: wrong teacher name" << endl;
            break;
        case ERR_DUPLICATED:
            cout << "ERROR: duplicated name" << endl;
            break;
        case ERR_PASSWORD:
            cout << "ERROR: wrong password" << endl;
            break;      
        case ERR_NO_QUESTIONS:
            cout << "ERROR: no pending questions" << endl;
            break;
        case ERR_ID:
            cout << "ERROR: wrong id" << endl;
            break;
        case ERR_ARGS:
            cout << "ERROR: wrong arguments" << endl;
    }
}

/*
 * constructor del struct question  
 * parámetros:
 * string question
 * string answer
 * int tema
 * int id
 * return: struct question
 * */
struct question ponerCuestion(string question, string answer,int tema, int id){
    struct question q;
    q.answer = answer;
    q.question = question;
    q.unit = tema;
    q.id = id;
    return q;

}

/* Función que muestra el menú de opciones
return: nada
*/
void showMenu() {
    cout << "1- Add question" << endl
         << "2- Batch add questions" << endl
         << "3- Delete question" << endl
         << "4- Add teacher" << endl
         << "5- Add answers" << endl
         << "6- View answers" << endl
         << "7- View statistics" << endl
         << "8- Export questions" << endl
         << "q- Quit" << endl
         << "Option: ";
}

/*
 * funcion addQuestion, se encarga de manegar la opción 1 del menú
 * parámetros:
 * Struct database
 * return struct database 
 * */
struct database addQuestion(struct database D){
    string unit, question; 
    int  unitNumber; // podría ser short pero me fio 0 del corrector
    bool barra;
    struct question Q;

    do{
        cout << "Enter unit: ";
        getline(cin, unit);

        if(unit.empty()){
            error(ERR_EMPTY);
            return D;
        }

        unitNumber = atoi(unit.c_str());

        if(unitNumber>5 || unitNumber<1){
            error(ERR_UNIT);
        }

    }while(unitNumber>5 || unitNumber<1);

    do {
        barra = false;
        cout << "Enter question: ";
        getline(cin, question);

        if (question.empty()) {
            error(ERR_EMPTY);
            return D;
        }

        for (unsigned int i = 0 ; i<question.size(); i++) {
            if (question[i]=='|') {
                barra = true;
            }
        }

        if (barra) {
            error(ERR_CHAR);
        } 

    }while (barra);

    Q = ponerCuestion(question, "", unitNumber, D.nextid);

    D.questions.push_back(Q);
    D.nextid++;

    return D;
}
struct database readFromFile(ifstream *fr, struct database D){
    string s, answer, question;
    int unsigned count = 0, emptyCount= 0, posBlanco;
    int countCorrectly = 0, unit;
    bool  blanco;

    while(getline(*fr, s)){
        blanco = true;
        count++;


        if(s.empty()){
            emptyCount++;
            continue;
        }

        for (unsigned int i = 0; i<s.size() && blanco; i++) {
            if (s[i]!=' ') {
                posBlanco = i;
                blanco = false;
            }
        }
        s.erase(0,posBlanco);

        // num|question|answer
        if(atoi(s.substr(0,s.find('|')).c_str())>5 || atoi(s.substr(0,s.find('|')).c_str())<1){
            cout << "Error line "<< count <<endl;
            continue;
        }

        unit = atoi(s.substr(0,s.find('|')).c_str());

        s.erase(0,s.find('|')+1);
        // question|answer

        // usar find
        // for (unsigned i = 0;noguion && i<s.size(); i++) {
        //     if(s[i]=='|'){
        //         pos = i;
        //         noguion =false;
        //     }
        // }


        if (string::npos==s.find_first_of('|')) {
            //cout << "pregunta: "<<s <<endl;
            // question
            if (s.empty()) {
                cout << "Error line "<< count <<endl;
                continue;
            }

            question = s;
            D.questions.push_back(ponerCuestion(question, "", unit, D.nextid+countCorrectly));
            countCorrectly++;

        }else {

            //cout <<"pregunta y respuesta:" <<s <<endl;
            question = s.substr(0, s.find_first_of('|'));

            if (question.empty()) {
                cout << "Error line "<< count <<endl;
                continue;
            }

            s.erase(0, s.find_first_of('|')+1);

            //cout <<"respuesta:" <<s <<endl;
            if (s.empty()) {
                cout << "Error line "<< count <<endl;
                continue;
            }

            if (string::npos!=s.find_first_of('|')) {
                cout << "Error line "<< count <<endl;
                continue;
            }

            answer = s;
            D.questions.push_back(ponerCuestion(question, answer, unit, D.nextid+countCorrectly));
            countCorrectly++;
        }
    }

    D.nextid += countCorrectly;
    cout << "Summary: " << countCorrectly<< "/"<< count-emptyCount<< " questions added"<< endl;
    fr->close();
    return D;

}

/*
 * funcion batchAddQuestion, se encarga de manejar la opcion 2 del menú
 * parámetros:
 * struct database 
 * return struct database
 * */
struct database batchAddQuestion(struct database D){
    string name;
    ifstream fr;

    do {
        cout << "Enter filename: "; 
        getline(cin, name);

        if (name.empty()) {
            error(ERR_EMPTY);
            return D;
        }

        fr.open(name);

        if (!fr.is_open()) {
            error(ERR_FILE);
        
        }
    }while (!fr.is_open());

    return readFromFile(&fr, D);


}


/*
 * función deleteQuestion se encarga de manejar la opción 3 del menú
 * parámetros struct database 
 * return struct database 
 * */
struct database deleteQuestion(struct database D){
    int pos; 
    unsigned int index;
    string aux;
    bool found;

    do {
        found = false;

        cout << "Enter question id: ";
        getline(cin, aux);

        if (aux.empty()) {
            error(ERR_EMPTY);
            return D;
        }

        index = atoi(aux.c_str());

        for (unsigned int i = 0; i< D.questions.size(); i++) {
            if(index == D.questions[i].id){
                pos = i;
                found = true;
            }
        }

        if (!found) {
            error(ERR_ID);
        }
    }while (!found);

    D.questions.erase(next(D.questions.begin(), pos));

    return D;
}

/*función quitarEspBlanco
 * se encarga de quitarle los espacios en blanco al nombre del profesor
 * en la función addTeacher
 * parámetros string s
 * return string 
 * */
string quitarEspBlanco(string s){
    int i = 0;
    while (s[i]==' ') {
        i++;
    }
    s.erase(0, i);
    i = s.length()-1;
    while (s[i]==' ') {
        i--;
    }
    //cout << i << endl; // debuggin stuff
    s.erase(i+1, s.length()-i);

    return s;
}

/*función encr, se encarga de encriptar las constraseñas
 * parámetros string s 
 * return string 
 * */
string encr(string s){
    for (unsigned int i = 0; i<s.length(); i++) {
        switch (s[i]) {
            case '1':
                s[i]='R';
                break;
            case '2':
                s[i]='W';
                break;
            case '3':
                s[i]='A';
                break;
            case '4':
                s[i]='G';
                break;
            case '5':
                s[i]='M';
                break;
            case '6':
                s[i]='Y';
                break;
            case '7':
                s[i]='F';
                break;
            case '8':
                s[i]='P';
                break;
            case '9':
                s[i]='D';
                break;
            case '0':
                s[i]='T';
                break;
        }
    }
    return s;
}

/* función addTeacher se encarga de manejar la opción 4 del menú
 * paráemtros struct database
 * return struct teacher
 * */
struct database addTeacher(struct database D){
    string s, passwrd;
    bool noalfab, tam ,dup, err;
    struct teacher T;

    do {
        noalfab = false;
        tam = false;
        dup = false;

        cout << "Enter teacher name: ";
        getline(cin, s);

        if (s.empty()) {
            error(ERR_EMPTY);
            return D;
        }


        for (unsigned int i = 0; i<s.length() && !noalfab; i++) {
            if (!isalpha(s[i]) && s[i]!=' ') {
                noalfab = true;
            }
        }

        s = quitarEspBlanco(s);

        if (3>s.length() || s.length()> KMAXNAME-1) {
            tam = true;
        }

        for (unsigned int i = 0; i<D.teachers.size(); i++) {
            if (s == D.teachers[i].name) {
                dup = true;
            }
        }

        if (dup) {
            error(ERR_DUPLICATED);
        }else if (tam || noalfab) {
            error(ERR_NAME);
        }

    }while (noalfab || tam || dup);
    
    do {
        err= false;
    
        cout << "Enter password: ";
        getline(cin, passwrd);

        if (passwrd.empty()) {
            error(ERR_EMPTY);
            return D;
        }

        for (unsigned int i = 0; i<passwrd.length(); i++) {
            if (!isdigit(passwrd[i])) {
                err = true;
            }
        }

        if (passwrd.length()!=4) {
            err =true;
        }

        if (err) {
            error(ERR_PASSWORD);
        }

    }while (err);

    passwrd = encr(passwrd);
    strcpy(T.name, s.c_str());
    strcpy(T.password, passwrd.c_str());
    T.answered = 0;
    D.teachers.push_back(T);
    return D;
}

/*
 * función addAnswers, se encarga de manejar la opción 5 del menú
 * parámetros struct database 
 * return struct database 
 * */
struct database addAnswers(struct database D){

    string teacherName, password, questionId, answer;
    unsigned int positionTeacher = 0, count = 0, posId;
    bool found, auth;

    do {
        found = false;

        cout << "Enter teacher name: ";
        getline(cin, teacherName);

        if (teacherName.empty()) {
            error(ERR_EMPTY);
            return D;
        }

        for (unsigned int i = 0; i<D.teachers.size(); i++) {
            if (D.teachers[i].name == teacherName) {
                found = true;
                positionTeacher = i;
            }
        }

        if (!found) {
            error(ERR_NAME);
        }
    }while (!found);

    do {
        auth = false;

        cout << "Enter password: ";
        getline(cin, password);

        if (password.empty()) {
            error(ERR_EMPTY);
            return D;
        }

        password = encr(password);
        auth = (password==D.teachers[positionTeacher].password);

        if (!auth) {
            error(ERR_PASSWORD);
        }
    }while(!auth);

    do {
        count = 0;

        for (unsigned int i = 0; i<D.questions.size(); i++) {
            if (D.questions[i].answer.empty()) {
                cout << D.questions[i].id << ". (" << D.questions[i].unit << ") " <<D.questions[i].question <<endl;
                count++;
            }
        }

        if (count == 0) {
            error(ERR_NO_QUESTIONS);
            return D;
        }

        do {
            found= false;

            cout << "Enter question id: ";
            getline(cin, questionId);

            if (questionId == "b") {
                // es muy mala practica usar esto como para cerrar el bucle, pero así me evito un código bastante complejo 
                return D;
            }

            if (questionId.empty()) {
                error(ERR_EMPTY);
                return D;
            }

            for (unsigned int i = 0; i<D.questions.size(); i++) {
                if (D.questions[i].id == (unsigned int) atoi(questionId.c_str())) {
                    found = true;
                    posId = i;

                }
            }

            if (!found) {
                error(ERR_ID);
            }
        }while (!found);

        do {

            cout << "Enter answer: ";
            getline(cin, answer);

            if (answer.empty()) {
                error(ERR_EMPTY);
                return D;
            }

            if (answer.find_first_of('|')!=string::npos) {
                error(ERR_CHAR);
            }

        }while(answer.find_first_of('|')!=string::npos);

        D.questions[posId].answer = answer;
        D.teachers[positionTeacher].answered++;

    }while (count !=0);

    return D;
}

/*
 * función viewAnswers, se encarga de manejar la opción 6 del menú
 * parámetros struct database 
 * */
void viewAnswers(struct database D){
    struct question q;
    for (unsigned int i = 0; i<D.questions.size(); i++) {
        if (!D.questions[i].answer.empty()) {
            q = D.questions[i];
            cout << q.id << ". (" <<q.unit << ") "<< q.question << ": " << q.answer << endl;
        }
    }
}

/*
 * función viewStatistics, se encarga de manejar la opción 6 del menú
 * parámetros struct database 
 * */
void viewStatistics(struct database D){
    unsigned int answered=0;

    cout<< "Total number of questions: "<<D.questions.size() << endl;
    for (unsigned int i = 0; i<D.questions.size(); i++) {
        if (!D.questions[i].answer.empty()) {
            answered++;
        }
    }

    cout<< "Number of questions answered: "<<answered << endl;
    for (unsigned int i =0; i<D.teachers.size(); i++) {
        cout << D.teachers[i].name<< ": "<< D.teachers[i].answered<< endl;
    }
}
/*
 * función exportQuestions se encarga de exportar las cuestiones en el archivo que le indiques
 * parámetros struct database 
 * */
void exportQuestions(struct database D){
    string filename;
    ofstream fr;

    do {

        cout << "Enter filename: ";
        getline(cin, filename);

        if (filename.empty()) {
            error(ERR_EMPTY);
            return;
        }

        fr.open(filename);

        if (!fr.is_open()) {
            error(ERR_FILE);
        }
    }while (!fr.is_open());

    for (unsigned int i = 0; i<D.questions.size(); i++) {
        if (D.questions[i].answer.empty()) {
            fr << D.questions[i].unit << "|"<< D.questions[i].question<<endl;
        }else {
            fr << D.questions[i].unit << "|"<< D.questions[i].question<<"|"<<D.questions[i].answer<<endl;
        }
    }

    fr.close();
}

void storeTeachers(struct database D){
    ofstream file;
    file.open(TEACHERFILE,ios::binary);

    if (!file.is_open()) {
        error(ERR_FILE);
        return;
    }

    for (unsigned int i = 0; i<D.teachers.size(); i++) {
        file.write((const char*)&D.teachers[i], sizeof(struct teacher));
    }

    file.close();
}

/*
 * función loadTeachers, se encarga de obtener los datos del binario (TEACHERFILE)
 * return: vector<teacher> 
 * */
vector<teacher> loadTeachers(){
    struct teacher t;
    vector<teacher> Teachers;
    ifstream file;
    file.open(TEACHERFILE, ios::in|ios::binary);

    if (file.is_open()) {
        while (file.read((char*)&t, sizeof(struct teacher))) {
            Teachers.push_back(t);
        
        }
    }
    return Teachers;

    
}
/*
 * función handlArgs se encarga de manejar los argumentos
 * parámetros 
 * struct database * 
 * int numArgs
 * char ** args
 * return
 * 1 => argumentos inválidos
 * 2 => argumento para cerrar el programa
 * 0 => argumento para continuar con el programa
 * */
int handlArgs(struct database *D, int numArgs, char** args){
    string parameter, fileName;
    ifstream fr;

    if (numArgs >4) {
        // se pasa de argumentos
        return 1;
    }else if (numArgs == 1) {
        // no hay argumentos
        return 0;
    }

    switch (numArgs) {
        case 2:

            if (strcmp(args[1], SFLAG)==0) {
                // está el -s
                viewStatistics(*D);
                return 2;

            }else {
                // no está en el único parámetro que hay
                return 1;
            }

            break;
        case 3:

            // dos parámetros
            if (strcmp(args[1], FFLAG) == 0) {
                fileName = args[2];

                fr.open(fileName);

                if (fr.is_open()) {
                    *D = readFromFile(&fr, *D);
                }else {
                    error(ERR_FILE);
                }

                return 0;
            }else {
                // no tiene sentido que no esté el -f al principio cuando solo hay 2 parámetros 
                return 1;
            }

            break;
        case 4:

            // tres parámetros 
            // el -f solo puede estar en las posiciones 1 o 2
            // y el -s solo puede estar en las posiciónes 3 o 1
            if (strcmp(args[1], FFLAG)==0) {
                if (strcmp(args[3], SFLAG)!=0) {
                    // -f loquesea no-s (combinación inválida)
                    return 1;
                }else {
                    fileName = args[2];

                    fr.open(fileName);

                    if (fr.is_open()) {
                        *D = readFromFile(&fr, *D);
                    }else {
                        error(ERR_FILE);
                    }

                    viewStatistics(*D);
                    return 2;

                }
            }else if (strcmp(args[2] , FFLAG) ==0) {
                if (strcmp(args[1], SFLAG)!=0) {
                    // no-s -f loquesea (combinación inválida)
                    return 1;
                }else {
                    fileName = args[3];

                    fr.open(fileName);

                    if (fr.is_open()) {
                        *D = readFromFile(&fr, *D);
                    }else {
                        error(ERR_FILE);
                    }
                    viewStatistics(*D);
                    return 2;
                }
            }

            break;
    }

    return 1;


}


// Función principal. Tendrás que añadir más código tuyo
int main(int argc, char *argv[]) {
    struct database data;
    data.nextid=1;
    char option;

    data.teachers = loadTeachers();

    switch (handlArgs( &data, argc, argv) ) {
        case 1:
            error(ERR_ARGS);
            return 1;
            break;
        case 2:
            return 1;
            break;
    }

    do{
        showMenu();
        cin >> option;
        cin.get();
        
        switch(option){
            case '1': // Llamar a la función "addQuestion" para añadir una nueva pregunta
                      data = addQuestion(data);
                break;
            case '2': // Llamar a la función "batchAddQuestion" para añadir preguntas desde fichero
                      data = batchAddQuestion(data);
                break;
            case '3': // Llamar a la función "deleteQuestion" para eliminar una pregunta
                      data = deleteQuestion(data);
                break;
            case '4': // Llamar a la función "AddTeacher" para añadir un nuevo profesor
                       data = addTeacher(data);
                break;
            case '5': // Llamar a la función "addAnswers" para añadir respuestas a las preguntas
                      data = addAnswers(data);
                break;
            case '6': // Llamar a la función "viewAnswers" para mostrar las preguntas con sus respuestas
                      viewAnswers(data);
                break;
            case '7': // Llamar a la función "viewStatistics" para ver las estadísticas de las preguntas
                      viewStatistics(data);
                break;
            case '8': // Llamar a la función "exportQuestions" para guardar las preguntas en fichero
                      exportQuestions(data);
                break;
            case 'q': // Salir del programa guardando los profesores en fichero
                      storeTeachers(data);                      
                break;
            default: error(ERR_OPTION);
        }
    }while(option!='q');

  return 0;
}
