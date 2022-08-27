#include <iostream>
using namespace std;

class Haha {
    private:
        int a;
        //int b(10); // it is not doable b(1) only in the class
        int c{10};
        int d = 1;
        //int& ref; // reference has to be initialized 
        //const int man = 10; // const has to be initialized
    public:
        void func() {
            //man = 30;
        }

        Haha() {// : man(10), ref(c) { //c++ will call default constructor when there is any constructor defined in class, if there is at least one constructor defined, c++ not gonna give you constructor
            cout << "Haha constructor" << endl;
            //man = 20;
        }
        Haha(int a, int b){ // : ref(a), man(b) {
            //it works
        }

        Haha(int a){ //} : ref(a) {
            cout << "Haha conversion constructor" << endl;
            //man = 30;
        }
        Haha(const Haha& a) {
            cout << "Haha copy constructor" << endl;
        }
        ~Haha() {
            cout << "Haha destructor" << endl;
        }
};

class Hehe {
    private:
        Haha a;
        Haha b;
        int c = 1;
        int *p = NULL;
    public:
        Hehe() :  b(a){
            a = Haha(10); // will call another Haha() conversion constructor even though it has been called when member initialization, and then conversion Haha() will be destructor right after it is copied to a;
            cout << "Hehe constructor" << c <<endl;
        }
        Hehe(int a) {
            c = a;
            cout << "Hehe conversion constructor" << endl;
        }
        ~Hehe() {
            cout << "Hehe destructor" << endl;
        }
};

class A{
    private:
        int a;
        int b;
        Hehe* p; // wont be call as data member as it is pointer
        //Hehe f;
        Haha d; // data member intialization does not follow the mil order
        //Hehe c; // alwayas follow the datamember order
        Hehe * p2;

    public:
        A(int a) : p2(new Hehe(10)) { //A(a, a) {
            cout << "MIL CONSTRUCTOR" << endl;
            p = new Hehe; // constructor will be called when new Hehe;
        }

        A(int a, int b) : d(), p(new Hehe), p2(new Hehe(10)) {
            this->a = a;
            this->b = b;
            cout << "Conversion Constructor" << endl;
        }
        void print() {
            cout << a << " " << b << endl;
        }
        ~A() {
            delete p;
            cout << "A DESTRUCTED" << endl;
            delete p2;
        }
};


int main() {
    //A a(3);
    //a.print();
    //A b = A(3);
    A c(3);

}