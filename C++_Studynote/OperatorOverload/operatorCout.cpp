#include <iostream>
using namespace std;

class Number {
    private:
        int v;
    public:
        Number(int v) : v(v) {}
        friend ostream& operator<<(ostream&, const Number&);
        friend Number operator+(const Number&, const Number&);
};

ostream& operator<<(ostream& os, const Number& n) {  // Return cout by reference, for further changes
    return os << n.v;
}

Number operator+(const Number& x, const Number& y) {
    return Number(x.v + y.v);
}

