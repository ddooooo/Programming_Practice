#include <iostream>
using namespace std;

class Complex {
    private:
        float real, imag;
    
    public:
        Complex(float r, float i) {
            real = r;
            imag = i;
        }
        
        void print() const {
            cout << real << ", " << imag << endl;
        }

        Complex add1(const Complex& x) {
            this->real += x.real;
            this->imag += x.imag;
            return (*this); // Return by Value
        }

        Complex* add2(const Complex& x){
            this->real += x.real;
            this->imag += x.imag;
            return this; // Return by Pointer
        }

        Complex& add3(const Complex& x){
            real += x.real;
            imag += x.imag;
            return (*this); //Return by Reference
        }
};

void f(const Complex a) {
    a.print();
};

void g(const Complex* a) {
    a->print();
}

void h(const Complex& a) {
    a.print();
}

int main() {
    int x = 2, y = 10;
    int* px, *py; // error => int* px, py -> py will be just integer not a pointer integer
    px = &x;
    py = &y;
    //cout << *px << *py << endl;

    py = px;
    const int * a2 = &x; //pointer to const // error -> *a2 = 10 cannot change the x through a2
    a2= &y; // changing the content of a(address) is doable
    int* const a1 = &y; //const pointer // error -> a1 = &x cannot change the content of a1
    *a1 = 20; // but changing the variable y through a1 is possible
    Complex u(10, 15);
    f(u); g(&u); h(u);

    cout << endl;

    Complex w(10, 10);
    Complex a(4, 5);
    a.add1(w).add1(w).print(); // a.add1(w) will create a temporary object and the temporary object will call add1(w) and create another temporary object to call print() since temporary object has value 24, 25, the output is 24, 25
    a.print(); // the output will be 14, 15
    cout << endl;

    Complex b(6, 7);
    b.add2(w)->add2(w)->print(); // b.add2(w) will not create a temporary object, and just call b, then call add2(w) and it also just call b, finally call print() output is 26, 27
    b.print(); // output 26, 27
    cout << endl;

    Complex c(7, 8);
    c.add3(w).add3(w).print(); // same as b.add2(w)->add2(w)->print() output 27, 28
     c.print(); // 27, 28
    cout << endl;

    Complex d(1, 2);
    d.add1(w).add2(w)->add3(w).print(); // d.add1(w) will create a temp object, then temp.add2(w) and then temp.add3(w) and then temp.print() output 31 , 32
    d.print(); // will call 11, 12
    cout << endl;

    Complex e(4, 5);
    e.add1(w).add3(w).print(); // e.add1(w) will call temp and then the temp.add3(w), and then temp.print() output 24, 25 
    e.print(); // 14, 15
    cout << endl;

    Complex f(3, 4);
    f.add3(w).add1(w).add2(w)->print(); // f.add3(w), and then f.add1(w) will create temp, so temp.add2(w) output 33, 34
    f.print(); //output 23, 24
    cout << endl;
}