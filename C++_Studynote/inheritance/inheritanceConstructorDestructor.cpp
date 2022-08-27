#include <iostream>
using namespace std;

class Base {
    public:
        Base() {cout << "Base's consturctor" << endl;}
        virtual void func() {
            cout << "Base function" << endl;
        }
        virtual ~Base() {cout << "Base's destructor" << endl;}
};

class Derived : public Base {
    public:
        Derived() {cout << "Derived's constructor" << endl;} //c++ automatically put Derived() : Base() //MIL so it will call Base Constructor too
        virtual ~Derived() {cout << "Derived's destructor" << endl;}
        virtual void func() override {
            cout << "Derived function" << endl;
        }
};

class Derived2 : public Derived {
    public:
        Derived2() : Derived(), Base() {  // mil only direct inheritance class, no indirect inheritance class
            cout << "Derived2 constructor" << endl;
        }
        ~Derived2() {
            cout << "Derived2 Destructor" << endl;
        }

        void func() { // even though func() has no keyword virtual or override, it it still a virtual function!!
            cout << "Dervied2 function" << endl; 
        }
};

void print_label(const Base& base){
    cout << "Base print" << endl;
}

void print_label(const Derived& derived) {
    cout << "Derived print" << endl;
}

int main() {
    Base a;
    Derived b;
    Derived2 c;

    Derived* p1 = &c; // if the derived does protected inhertance, the base pointer cannot get the reference of derived class

    p1->Derived::func(); // if will call func() in Derived class, even it func() is virtual function

    int* q = new int[5];
    

    Base d = b;
    d.func();

    a =b; //Slicing only occurs when object copying
    //b = a; error

    Base* aptr = &a;

    //Liskov
    Derived* bptr = &b;

    //Poly
    Base* abptr = &b;
    //Derived* baptr = &a; error 
    int nm = 1;
    int mn = 20;
    int& ref = nm;
    ref = mn;

    Base& r = b;

    Base& d = b;
    //d = b;
    d = c;
    //Derived& d = a; error

    print_label(b); // will call print_label(const Derived..)
    print_label(c); // type of c -> Base, type of b -> Derived,, will call print_label(const Base&..)
    

    Base* p = new Derived;
    delete p;

    cout << "Protected one" << endl;

    cout << " " << endl;

    Derived2 d;
}