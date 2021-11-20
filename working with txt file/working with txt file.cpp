// working with txt file.cpp :

#include <iostream>
#include<string>
#include<fstream>
using namespace std;

struct birthday {
    int day;
    int month;
    int year;

};

struct subject {
    string name;
    float point;
};

struct student {
    string name;
    string id;
    birthday day;
    int number_of_subjects;
    subject sub[100];
};

void read_birthday(ifstream& filein, birthday& a) {
    filein >> a.day;
    char x;
    filein >> x;
    filein >> a.month;
    filein >> x;
    filein >> a.year;
}

void read_subject(ifstream& filein, subject a[], int number_of_subjects) {
    for (int i = 0; i < number_of_subjects; i++) {
        getline(filein, a[i].name, ':');
        filein >> a[i].point;
    }
}

void read_file(ifstream& filein, student arr[], int& number_of_students) {
    filein.open("student.txt", ios_base::in);
    int i = 0;
    while (!filein.eof()) {
        getline(filein, arr[i].name, ',');
        getline(filein, arr[i].id, ',');
        read_birthday(filein, arr[i].day);
        filein >> arr[i].number_of_subjects;
        read_subject(filein, arr[i].sub, arr[i].number_of_subjects);
        i++;
    }
    number_of_students = i;
    filein.close();
}

void process_data(student arr[], int number_of_students) {
    for (int i = 0; i < number_of_students; i++) {
        if (arr[i].name.at(0) == '\n') {
            arr[i].name.erase(arr[i].name.begin());
        }
        for (int j = 0; j < arr[i].number_of_subjects; j++) {
            if (arr[i].sub[j].name.at(0) == '\n') {
                arr[i].sub[j].name.erase(arr[i].sub[j].name.begin());
            }
        }
    }
}

void show(student a) {
    cout << "information student:\n";
    cout << "\tname: " << a.name << endl;
    cout << "\tid: " << a.id << endl;
    cout << "\tbirthday: " << a.day.day << "/" << a.day.month << "/" << a.day.year << endl;
    cout << "\tnumber of subjects: " << a.number_of_subjects << endl;
    for (int j = 0; j < a.number_of_subjects; j++) {
        cout << "\t\tsubject " << j + 1 << ": " << a.sub[j].name << endl;
        cout << "\t\tpoint of subject " << j + 1 << ": " << a.sub[j].point << endl;
    }
}

void show_information_student(string name_student,student arr[],int number_of_students) {
    bool check = false;
    for (int i = 0; i < number_of_students; i++) {
        if (name_student == arr[i].name) {
            show(arr[i]);
            check = true;
            break;
        }
    }
    if (!check) {
        cout << "not found\n";
    }
}

void write_information_student(student a,ofstream &fileout,int i) {
    fileout << "ifnormation student :\n";
   
    fileout << "number " << i + 1 << ":\n ";
    fileout << "\tname: " << a.name << endl;
    fileout << "\tid: " << a.id << endl;
    fileout << "\tbirthday: " << a.day.day << "/" << a.day.month << "/" << a.day.year << endl;
    fileout << "\tnumber of subjects: " << a.number_of_subjects << endl;
    for (int j = 0; j < a.number_of_subjects; j++) {
        fileout << "\t\tsubject " << j + 1 << ": " << a.sub[j].name << endl;
        fileout << "\t\tpoint of subject " << j + 1 << ": " << a.sub[j].point << endl;
    }
    fileout << "\n--------------------\n";
}

void write_file(int year,student arr[],int number_of_students,ofstream &fileout) {
    fileout.open("students born in the year.txt", ios_base::out);
    bool check = false;
    for (int i = 0; i < number_of_students; i++) {
        if (arr[i].day.year == year) {
            write_information_student(arr[i], fileout,i);
            check = true;
        }
    }
    if (!check) {
        fileout << "there are not student \n";
    }
    
    fileout.close();
}

int main()
{
    ifstream filein;
    student arr[100];
    int number_of_students;
    read_file(filein, arr, number_of_students);
    process_data(arr, number_of_students);

    string name_student;
    cout << "enter name student:\n";
    getline(cin, name_student);
    show_information_student(name_student, arr, number_of_students);
    int year;
    cout << "enter year\n";
    cin >> year;
    ofstream fileout;
    write_file(year, arr, number_of_students, fileout);
    return 0;
}