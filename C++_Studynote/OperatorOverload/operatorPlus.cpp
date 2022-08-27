#include <iostream>
using namespace std;

class Number {
    private:
        int v;
    public:
        Number(int v) : v(v) {}
        friend ostream& operator<<(ostream&, const Number&);
        Number operator+(const Number& a) {
            return Number(v + a.v);
        } // Memberfunction -> operator+(const Number* this, const Number& a)
};

int main() {
    Number a(10);
    Number b(20);

    a + b; // a.operator+(b)
    5 + a; // not work as 5.operator(a) 5 is integer, c++ not gonna change 1 to Number object
}

