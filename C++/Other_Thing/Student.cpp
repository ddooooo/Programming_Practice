#include "Student.h"

Student::Student(int age, string name){
    this->age = age;
    this->name = name;
}

int Student::getAge(){
    return age;
}

string Student::getName(){
    return name;
}
