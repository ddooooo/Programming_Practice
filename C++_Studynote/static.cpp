#include <iostream>
using namespace std;


// static variable is similar to global object// Difference is static variable can be put under private
class Haha {
    private:
        int a;
        double b;
        static int c; // this static variable will not be created in the box of Haha object
    
    public:
        Haha() {cout << "HAHAA" << endl;}
        static int d; // it will not be defined
        static const int e = 20; // only constant integer variable will not need initialization in global
        static void func() {
            //a = 10;
            //b = 20; error since a and b is not static data member
            c = 40; // static member function is only access to static data member variable
        }
        void func() {
            c = 10;
        }
};

class Hehe {
    private:
        static Haha obj;
    public:
        static int d;
};

Haha Hehe::obj; // created before entering main function
int Haha::d; // defined in the global 
int Hehe::d;

int main() {
    Haha obj;
    //Haha::c = 20; c is private variable error
    obj.d = 20;
    obj.func();
    Haha::d = 30;
    Hehe obj2;
    Haha::func();
    
}