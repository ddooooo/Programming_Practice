#include <iostream>
#include <typeinfo>
using namespace std;

class Base {
    public:
        void f() const {
            cout << "function in BASE" << endl;
        }
};

class A : public Base{
    public:
        virtual void f() const {
            cout << "f in A" << endl;
        }
        //int max(int a, int b) {}
        //long max(long a, long b) {} // both are similar but actually different function - polymorphism(function overloadind)
};

class B : public A {
    public:
        virtual void f() const { //f() in A and B are similar but different -function overriding (polymorphism)
            cout << "f in b" << endl;
        }
};

void haha(A* p) {
    p->f();
}

int main() {
    B obj;
    haha(&obj); // call f in class A // if virtual call f() in class B
    obj.f(); //call f in class B no virtual 
    A* p = &obj;
    p->f(); // call f in class A but call f in class B if f is virtual function
    Base* p1 = &obj;
    p1->f(); //call f in class Base because f() is not virtual
    typeid(*p); // returns another object (typeinfo) that carries the type of object
    cout << typeid(*p).name() << endl; // only correct when class has virtual function
    cout << typeid(*p1).name() << endl;
}