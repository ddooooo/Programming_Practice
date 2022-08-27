#include <iostream>
using namespace std;

class Student{
    private:
        int age;
        string name;

    public:
        Student(int age, string name);
        int getAge();
        string getName();

};