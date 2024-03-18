#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>

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


    while(1){
getline(fr, s);
        /*
        if(s.empty()) 
            continue;

        if(s[0]>5 || s[0]<1){
            count++;
            continue;
        }
        unit = stoi(s.substr(1,1));

        s.erase(0,2);
        for (unsigned i = 0;noguion && i<s.size(); i++) {
            if(s[i]=='|'){
                pos = i;
                noguion =false;
            }
        }
        if (!noguion) {
            if ((pos == s.size() || pos == 0) ) {
                count++;
                continue;
            }

            question = s.substr(0, pos);
            s.erase(0, pos);
            answer = s;

            D.questions.push_back(ponerCuestion(question, answer, unit, D.nextId+countCorrectly));
            count++;
            countCorrectly++;
        }
        question = s;
        D.questions.push_back(ponerCuestion(question, "", unit, D.nextId+countCorrectly));
        count++;
        countCorrectly++;
        */
        cout << s<<endl;

    }

}
struct Database deleteQuestion(struct Database D){
    int pos, index;
    string aux;
    bool found;
    cout << "Enter question id: ";
    getline(cin, aux);
    index = stoi(aux);
    for (unsigned int i = 0; i< D.questions.size(); i++) {
        if(index == D.questions[i].id){
            // more stuff

        }
    
    }

    

}

void addTeacher(){

}
void addAnswers(){

}
void viewAnswers(){

}
void viewStatistics(){

}
void exportQuestions(){

}
// Función principal. Tendrás que añadir más código tuyo
int main(int argc, char *argv[]) {
    Database data;
    data.nextId=1;
    char option;
    
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
                break;
            case '4': // Llamar a la función "AddTeacher" para añadir un nuevo profesor
                break;
            case '5': // Llamar a la función "addAnswers" para añadir respuestas a las preguntas
                break;
            case '6': // Llamar a la función "viewAnswers" para mostrar las preguntas con sus respuestas
                break;
            case '7': // Llamar a la función "viewStatistics" para ver las estadísticas de las preguntas
                break;
            case '8': // Llamar a la función "exportQuestions" para guardar las preguntas en fichero
                break;
            case 'q': // Salir del programa guardando los profesores en fichero
                break;
            default: error(ERR_OPTION);
        }
    }while(option!='q');

  return 0;
}
