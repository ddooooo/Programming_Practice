#include <iostream>
using namespace std;

const int mystery8(int a, double b) { cout << "mystery8" << endl; }

int main() {
    const int(*p4)(const int, const double) = mystery8;
    int a = 20;
    int b = 30;
    int* pa = nullptr;
    int* pb = &b;

    cout << ++a << endl; // first increase the variable and then assigned
    cout << a++ << endl; // first assigned the value and then increase

    int c = ++a;
    cout << c << endl;
    c = a++;
    cout << c << endl;

    if(pb) { // check if the pointer is nullptr or not
        cout << " what" << endl; // if the pointer is not nullptr
    }else 
        cout << "YESYES" << endl;  // if the pointer is nullptr

    int *x = &a;
    a++;
    cout << *x << "  " <<  a << endl;
    ++a;
    cout << *x << "  "  << a << endl;
    ++(*x);
    cout << *x << "  "  << a << endl;
    (*x)++;
    cout << *x << "  "  << a << endl;

    int * iptr = &a;
    const int* ptrc = &b; // pointer to const
    int * const cptr = &b; // const pointer
    ptrc = &a;
    ptrc++; // change the address of the pointer is valid
    *ptrc = a; // change the value of pointer is NOT valid
    
    const int wow;
    iptr = new int[10];
    
    a = *ptrc; // valid
    b = *cptr; 
    ptrc = iptr; // valid
    ptrc = cptr;
    iptr = ptrc; // assign const int* to int* is not valid
    iptr = cptr; // valid


    int& ref; // error reference always has to be bounded to an object
    int& ref1 = iptr; // type is mismatched, it should be int*& ref1 = iptr;
    int& ref2 = a;
    ref2 = b; 
    int& ref3 = *ptrc;
    ref3 = *cptr;
    const int& ref4 = *ptrc;
    const int& ref5 = *cptr;

    const int** pptr = new const int*;
    *pptr = new int;
    **pptr = 5; // pptr is pointer to const, it cannot change anything through *pptr
}