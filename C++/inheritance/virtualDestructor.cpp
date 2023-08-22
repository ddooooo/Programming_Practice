#include <iostream>
using namespace std;
class Base {
    private:
        int* p;
    public:
        Base() {
            p = new int[5];
            func(); // will call base function with non const 
        }
        virtual void func() { 
            cout << "base function" << endl;
        }

        virtual void func() const { // member function with const is different
            cout << "base function const" << endl;
        }

        ~Base() {
            delete p;
            cout << "Base destructor" << endl;
        }
};

class Derived : public Base {
    private:
        int* p;
    public:
        Derived() {
            p = new int[5];
            func();
        }
        virtual void func() override {
            cout << "Derived function" << endl;
        }

        /*virtual void func() override const { // override keyword always has to be after 'const' keyword
            cout << "Derived function const" << endl;
        }*/
        ~Derived() {
            delete p;
            cout << "Derived destructor" << endl;
        }
};

int main() {
    Base d;
    cout << " " << endl;
    Base* p = new Derived; 
    delete p;
}