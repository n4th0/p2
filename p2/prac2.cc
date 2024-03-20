#include <iostream>
#include <cctype>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <string>

using namespace std;

const int KMAXNAME = 50;
const int KMAXPASSWORD = 5;

// Registro para las preguntas
struct Question{
    unsigned int id;
    unsigned int unit;
    string question;
    string answer;
};

// Registro para los profesores
struct Teacher{
    char name[KMAXNAME];
    char password[KMAXPASSWORD];
    unsigned int answered;
};

// Registro para la base de datos
struct Database{
    unsigned int nextId;
    vector<Question> questions;
    vector<Teacher> teachers;
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
struct Question ponerCuestion(string question, string answer,int tema, int id){
    struct Question q;
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
// function developed by the pupil
void loadTeachers(){

}

struct Database addQuestion(struct Database D){
    string unit, question; 
    int unitNumber;
    bool barra;
    struct Question Q;
    do{
        cout << "Enter unit: ";
        getline(cin, unit);
        if(unit.empty()){
            error(ERR_EMPTY);
            return D;
        }
        unitNumber = stoi(unit);
        if(unitNumber>5 || unitNumber<1){
            error(ERR_UNIT);

        }
    }while(unitNumber>5 || unitNumber<1);

    do {
        barra = false;
        cout << "Enter question: ";
        getline(cin, question);

        for (unsigned int i = 0 ; i<question.size(); i++) {
            if (question[i]=='|') {
                barra = true;
            }
        }

        if (barra) {
            error(ERR_CHAR);
        } else if (question.empty()) {
            error(ERR_EMPTY);
        }
    }while (barra || question.empty());

    Q = ponerCuestion(question, "", unitNumber, D.nextId);

    D.questions.push_back(Q);
    D.nextId++;

    return D;

}
struct Database batchAddQuestion(struct Database D){

    string name, s, answer, question;
    int unsigned count = 0, pos = 0;
    int countCorrectly = 0, unit;
    bool noguion = true;
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


    while(getline(fr, s)){
        count++;

        noguion = true;

        if(s.empty())
            continue;


        if(atoi(s.substr(0,1).c_str())>5 || atoi(s.substr(0,1).c_str())<1){
            cout << "Error line "<< count <<endl;
            continue;
        }

        unit = stoi(s.substr(0,1));

        s.erase(0,2);

        for (unsigned i = 0;noguion && i<s.size(); i++) {
            if(s[i]=='|'){
                pos = i;
                noguion =false;
            }
        }


        if (!noguion) {
            if (pos == s.size()-1 || pos == 0)  {
                cout << "Error line "<< count <<endl;
                continue;
            }

            question = s.substr(0, pos-1);
            s.erase(0, pos);
            answer = s;

            D.questions.push_back(ponerCuestion(question, answer, unit, D.nextId+countCorrectly));
            countCorrectly++;
        }else {
            question = s;
            D.questions.push_back(ponerCuestion(question, "", unit, D.nextId+countCorrectly));
            countCorrectly++;
        }
    }


    D.nextId += countCorrectly;
    cout << "Summary: " << countCorrectly<< "/"<< count << " question added"<< endl;
    fr.close();
    return D;

}
struct Database deleteQuestion(struct Database D){
    int pos; 
    unsigned int index;
    string aux;
    bool found;

    do {
        cout << "Enter question id: ";
        getline(cin, aux);
        index = stoi(aux);
        found = false;
        if (aux.empty()) {
            error(ERR_EMPTY);
            return D;
        }
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
    //cout << i << endl;
    s.erase(i+1, s.length()-i);

    return s;
}
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
struct Teacher addTeacher(struct Database D){
    string s, passwrd;
    bool noalfab, tam ,dup, err;
    struct Teacher T;
    do {
        noalfab = false;
        tam = false;
        dup = false;

        cout << "Enter teacher name: ";
        getline(cin, s);
        if (s.empty()) {
            error(ERR_EMPTY);
            return T;
        }


        for (unsigned int i = 0; i<s.length(); i++) {
            if (!isalpha(s[i]) && s[i]!=' ') {
                noalfab = true;
            }
        }

        s= quitarEspBlanco(s);

        if (3>s.length() || s.length()> KMAXNAME-1) {
            error(ERR_NAME);
            tam = true;
        }
        for (unsigned int i = 0; i<D.teachers.size(); i++) {
            if (s == D.teachers[i].name) {
                error(ERR_DUPLICATED);
                dup = true;
            }
        }

        //cout << s << noalfab << tam << dup;
    }while (noalfab || tam || dup);
    
    do {
        err= false;
    
        cout << "Enter password: ";
        getline(cin, passwrd);

        if (passwrd.empty()) {
            error(ERR_EMPTY);
            return T;
        }
        for (unsigned int i = 0; i<passwrd.length(); i++) {
            if (!isdigit(passwrd[i])) {
                err = true;
            }
        }
        if (passwrd.length()>4) {
            error(ERR_PASSWORD);
            err =true;

        }
    }while (err);

    passwrd = encr(passwrd);
    strcpy(T.name, s.c_str());
    strcpy(T.password, passwrd.c_str());
    T.answered = 0;
    return T;
}

struct Database addAnswers(struct Database D){

    string teacherName, password, questionId, answer;
    unsigned int positionTeacher, count = 0;
    bool found, auth;

    do {
        found = false;
        cout << "Enter teacher name: ";
        getline(cin, teacherName);
        for (unsigned int i = 0; i<D.teachers.size(); i++) {
            if (D.teachers[i].name == teacherName) {
                found = true;
                positionTeacher = i;
            }
        }

        if (teacherName.empty()) {
            error(ERR_EMPTY);
            return D;
        }
        if (!found) {
            error(ERR_NAME);
        }

    }while (!found);

    do {
        auth = false;
        cout << "Enter password: ";
        getline(cin, password);
        password = encr(password);
        auth = (password==D.teachers[positionTeacher].password);
        if (password.empty()) {
            error(ERR_EMPTY);
            return D;
        }
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

        do {
            found= false;

            cout << "Enter question id: ";
            getline(cin, questionId);

            if (questionId == "b") {
                // es muy mala practica usar esto como para cerrar el bucle, pero así me evito un código bastante complejo 
                return D;
            }

            if (count ==0) {
                error(ERR_NO_QUESTIONS);
                return D;
            }
            if (questionId.empty()) {
                error(ERR_EMPTY);
                return D;
            }
            for (unsigned int i = 0; i<D.questions.size(); i++) {
                if (D.questions[i].id == (unsigned int) atoi(questionId.c_str())) {
                    found = true;
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

        cout << "Llego a guardar"<<endl;

        // esto no guarda por algun tipo de razón
        D.questions[atoi(questionId.c_str())].answer = answer;

    }while (count !=0);

    // nunca debería llegar aqui (preguntar en clase sobre la mala practica de salir con un return en el caso de la "b")
    return D;
}

void viewAnswers(struct Database D){
    struct Question q;
    for (unsigned int i = 0; i<D.questions.size(); i++) {
        if (!D.questions[i].answer.empty()) {
            q = D.questions[i];
            cout << q.id << ". (" <<q.unit << ") "<< q.question << ": " << q.answer << endl;
        }
    }
}
void viewStatistics(struct Database D){
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

void exportQuestions(struct Database D){
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
// Función principal. Tendrás que añadir más código tuyo
int main(int argc, char *argv[]) {
    Database data;
    data.nextId=1;
    char option;
    struct Teacher t;
    
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
                       t = addTeacher(data);
                       data.teachers.push_back(t);

                break;
            case '5': // Llamar a la función "addAnswers" para añadir respuestas a las preguntas
                      data = addAnswers(&data);
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
                break;
            default: error(ERR_OPTION);
        }
    }while(option!='q');

  return 0;
}
