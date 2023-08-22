#include <iostream>
using namespace std;

class A {
    public:
        A() {
            cout << "Default Constructor A" << endl;
        }
        A(const A& a) {
            cout << "Copy Constructor A" << endl;
        }
        A(int a) {
            cout << "Conversion Constructor A" << endl;
        }
        ~A() {
            cout << "Destructor A" << endl;
        }
};

class B {
    private:
        A c;
    public:
        B(){
            cout << "Default constructor B" << endl;
        }

        B(const B& a) {
            cout << "Copy Constructor B" << endl;
        }

        B(A a){
            A b;
            cout << "Wow" << endl;
            c = A(10); // it is equal sign, which means it is equal operator, not calling copy constructor
            cout << "Wow2" << endl;
            c = A(); // it is calling default constructor, different from just A();-> it is function prototype that you will define later
            cout << "Conversion Consturctor B" << endl;
        }

        ~B() {
            cout << "Destructor B" << endl;
        }
};

class C {
    private:
        A a;
        B b;
    public:
        C() : a(), b() {
            B b = A(); // It first call B' constructor(temp) and then equal operator, and then as soons as it is copied to 'b' then it will be killed(Destructor) 
            cout << "default Constructor C" << endl;
        }
};

int main() {
    B b();
    //cout << "Show time" << endl;
    //B(10);
    C c;
}