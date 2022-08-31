#include <iostream>
using namespace std;

//Override function 
//- normally for inheritance classes, If there are function with the same name and same parameter, but has different execution
//- is also called redefining virtual function
//functionA with const and functionA without const is not override, just different kind of function
//Overload function 
//-Same name but different parameter 

//Inheritance A to B create 'B *is a* A' relationship
//*has a* relationship is when class A has pointer to another class B
class Ground {
    private:
        int a;
        int b;
        const int c;
    public:
        Ground() : c(10) {
            //cout << "Default Ground Constructor" << endl;
        }
        Ground(int a, int b) : a(a), b(b), c(10){ //const number variable can be changed by mil
            //c = 20; // cannot be changed in consturctor body
            //cout << "Conversion Ground" << endl;
        }

        virtual void pureVirtualFunc() = 0;

        void getPrivate() const
        {
            cout << "Non-virtual function" << endl;
        }

        void funcGround() {
            cout << "function in Ground " << a << " " << b << endl;
        }

        virtual void FuncInherit()
        {
            cout << "Override function in ground" << endl;
        }
};

class Base : public Ground{
    private:
        float a;
        float b;
    public:
        Base() : a(10.6), b(20.6) {
            //cout << "Default Base Constructor" << endl;
        }
        Base(float a, int b) : a(a), b(b) {
            //cout << "Conversion Base" << endl;
        }

        virtual void pureVirtualFunc()
        {
            cout << "Pure virtual function in base" << endl;
        }

        void funcBase() {
            cout << "function in Base " << a << " " << b << endl;
        }

        void FuncInherit()
        {
            cout << "Override function in base" << endl;
        }
};

class Derived : public Base {
    private:
        Base a;
    public:
        Derived() : Base(10, 20) {  // if there is no base default constructor defined in Base class, error
            //cout << "Derived Constructor" << endl;
        }
        void funcDerived() {
            cout << "Function in Derived" << endl;
        }

        void FuncInherit()
        {
            cout << "Override function in derived" << endl;
        }

};

int main() {

    // Review
    // Base a;
    // a.FuncInherit();

    // Derived b;
    // b.FuncInherit();

    Ground g; // abstract class cannot be initialize 

    Ground* gp = new Derived();
    gp->FuncInherit();
    gp->getPrivate();

    cout << endl;


    Base b;
    b.getPrivate();

    //Derived a;
    //a.funcBase();
    //Base d = Derived(); // will call Derived Constructor
    //Base* p = new Derived(); // will call Derived Constructor
    //p->funcBase();
    //p->funcDerived(); // error// it checks the type of p
    //d.funcDerived(); // always check on type of d;
    //Base* p2 = new Derived;
    //Base b;

    // Ground c = Base(10, 20);
    // c.funcGround();
    // //Slicing
    // //c = b;

    // Ground g(1, 20);
    // Base ba;

    // Derived z;
    // Derived* p = new Derived(z);

    // Ground* gp = &g;
    // gp = &ba;
    // Base* bp = &ba;

    // gp->funcGround();
    // bp->funcBase();

    // Derived ok;
    // ok.funcGround(); // it will be searched up to class Ground to find a functionGround() 

    
}   