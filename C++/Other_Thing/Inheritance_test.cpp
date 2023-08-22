#include <iostream>
using namespace std;

class Base {
    private:
        int a;
    public:
        Base() {cout << "Base's consturctor" << endl;}
        Base(int a) {cout << "Base's conversion constructor" << endl;}
        virtual void func() {
            cout << "Base function" << endl;
        }
        virtual ~Base() {cout << "Base's destructor" << endl;}
};

class Derived : public Base {
    public:
        Derived() { cout << "Derived's constructor" << endl;} //c++ automatically put Derived() : Base() //MIL so it will call Base Constructor too
        Derived(const Base& d) { cout << "Derived's copy constructor" << endl;}
        virtual ~Derived() {cout << "Derived's destructor" << endl;}
        virtual void func() override {
            cout << "Derived function" << endl;
        }
        void func2() {
            cout << "Func2" << endl;
        }
};

class Derived2 : public Derived {
    public:
        Derived2() : Derived() /*Base()*/ {  // mil only direct inheritance class, no indirect inheritance class
            cout << "Derived2 constructor" << endl;
        }
        ~Derived2() {
            cout << "Derived2 Destructor" << endl;
        }

        void func() { // even though func() has no keyword virtual or override, it it still a virtual function!!
            cout << "Dervied2 function" << endl; 
        }
};

void testing(Base&& a) {
    cout << "it is a move object lvalue" << endl;
}

void testing(const Base& a) {
    cout << "it is a rvalue" << endl;
}

int main() {
    Base* p = new Derived; // legal, as parents can points at its child
                           // It will create Derived type object -> 1. call its parents 2. Initialize all data members 3. call itself  
                           // but the type is always Base!!!
    //Derived d1(*p);        // copy constructor will also call its parents 
    //Base* test = new Derived( *(Derived*)(p) );
    //Base *d2;
    Derived a;
    a.func();
    (Derived*)(p);
    p->func();
    dynamic_cast<Derived*>(p);
    p->func();
    Base*(test) = new Derived;
    Base*test2;
    testing(*test);
    testing(Base());
    cout << "edn" << endl;
}