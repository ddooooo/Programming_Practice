#include <iostream>
using namespace std;

class A {
    private:
        int a;
        static const int b;
        const int c;
        static int d;

    public:
        A() : a(10), b(20), c(30), d(40) // initialization
        {
            // Assignment
            a = 10;
            b = 20; // static const cannot be assignment()
            c = 30;
            d = 40; 
        }

        void add() {
            a += 1;
        }

        void substract(const int& a) {
            a += 1; //error, a is const int reference
            this->a -= a;
        }

        void ahha(int& a) {
            this->a += a;
        }

        void print() const { // it does not modify the data member function compiled to void print(const A* this)
            cout << a << endl;
            a += 1; // error
        }

        const int func(int num) const
        {
            num += 1;
            num += a;
            num += c;
        }

};

int main() {
    A a; // non const object can call both non const and const 
    const A b; // const object cannot call non const member function
    
    a.add();
    a.print();
    b.add(); // since b is const object, it cannot be modified also it cannot call non const member fucntion
    b.print();
    int x = 10;
    const int cx = 20;
    a.substract(x);
    a.substract(cx);
    a.ahha(x); // non const reference parameter accept non const variable int& x = int y is okk
    a.ahha(y); // non const reference parameter can't accept const variable // int& x = const int y noooo
    const int& cref = x;
    int& ref2 = cref;
    int& ref = cx;   
    const int& cref2 = cx;
    const int& cref3 = ref;
    const int& cref4 = cref2;
    const int c = x;
    const int d = y;
    const int f = cref;
    const int g = ref;
    int e = y;
    x = y;
    e = cref; // int e = const int& is okkk

    ref = x;
    int& const mystery = cref;
    int& const mystery2 = ref;
    int& const mystery3 = x;
    int& const mystery4 = y;
}