#include <iostream>
using namespace std;

class A{
    public:
        A() {cout << "A default constructor" << endl;}
        A(const A& a) {cout << "A copy constructor" << endl;}
        ~A() {cout << "A Destructor" << endl;}
};

class B{
    public:
        B() {cout << "B default constructor" << endl;}
        B(B& b) {cout << "B copy constructor" << endl;}
        ~B() {cout << "B Destructor" << endl;}
};

class AB{
    private:
        A a;
        B b;
    public:
        AB(const A& a1, const B& b1) {
            //a(a1);
            //b{b1};
            cout << "Constructor AB with const A& and const B&" << endl;
        }
        AB(A&& a2, B&& b2): a(a2), b(b2) {
            cout << "Move Consturctor" << endl;
        }
};

int main() {
    A a;
    B b;
    AB(a, b); // it will be destructed right after it has been created because it is temporary object that is not bounded to any object
    AB(move(a), move(b)); // same as AB(a, b), it is also temporary object
    AB ab1(a, b); // it is named object
    AB ab2(move(a), move(b)); // it is named object
    cout << "OUYT! " << endl;
    int no{10};
    no{20};
}