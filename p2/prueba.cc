
#include <iostream>
#include <vector>
#include <fstream>
#include <vector>
#include <iostream>

#define TEACHERFILE "teachers.bin"

using namespace std;

const int KMAXNAME = 50;
const int KMAXPASSWORD = 5;

struct teacher{
    char name[KMAXNAME];
    char password[KMAXPASSWORD];
    unsigned int answered;
};

vector<teacher> loadTeachers(){
    struct teacher T;
    vector<teacher> Teachers;
    ifstream file;
    file.open(TEACHERFILE, ios::in|ios::binary);

    if (file.is_open()) {
        while(file.read((char *)&T, sizeof(struct teacher))){
            Teachers.push_back(T);
        }
        file.close();
    }

    return Teachers;
}

int main(){
    loadTeachers();
    return 0;
}
