#include <iostream>
using namespace std;

class A{
    public:
        virtual void func() {
            cout << "A's func()" << endl;
        }
};

class B: public A{
    public:
        void func() {
            cout << "B's func()" << endl;
        }
};

int main() {
    A a;
    B b;
    a.func();
    
    A* bp = &b;
    bp->func();
    cout << "hihi" << endl;
}