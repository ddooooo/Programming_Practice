#include <iostream>
using namespace std;

int global = 30;

int main() {
    int a=1;
    int b=2;
    int c=3;

    //auto f = [](int x) { return a*x*x + b*x + c;}; // without the capturing local variable cannot be used in lamda function
    auto f = [](int x) {return x + global;}; // global variable can be used without capturing
    //auto f = [global](int x) {return x+ global;}; // capturing global variable is illegal
    auto g = [=](int x) { return a*x*x + b*x + c;}; // [=] captures all local variable by value
    auto h = [&](int x) { return a*x*x + b*x + c;}; // [&] captures all local variable by reference
    //auto f = [a, b](int x){ return a*x*x + b*x + c;}; // captures only a and b by values 
    auto i = [&a, b](int x){ return a*x*x + b*x;}; // captures by reference
    auto j = [=, &a](int x){ return a*x*x + b*x;};
    cout << f(5) << endl;
    cout << g(5) << " " <<  h(5) << endl;
    a = 2;
    b = 4;
    c = 5;
    cout << g(5) << " " <<  h(5) << endl; // lamda function that captures by value wont affected by changed of local variable

    int p1 = 1;
    int p2 = 2;

    for(int i=0; i<3; ++i) {
        auto f = [=](int c) { cout << p1 + p2 + c << endl; };
        f(1);
        ++p1;
        ++p2;
    }
}