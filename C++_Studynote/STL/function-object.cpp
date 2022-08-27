#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Haha {
    public:
        bool operator()(int v) { // the return depends on what you want to do with operator() // parameter type can be any type, even nothing
            return v > a;
        }
        Haha(int a) : a(a) {}
    private:
        int a;
};

void testing(int x, int y, Haha a) {
    
    cout << a(x) << endl;
    cout << a(y) << endl;
}

int main() {
    Haha haha(6); // constructing an object haha -> not function object

    cout << haha(2) << endl; // how can it works, overloading 'operator()' -> must be member function, looks like function call but it is object, so function object
    // function object -> object with () // must have at least one operator()// if the return type is boolean, it can be predicate -> STL find_if()

    testing(10, 20, haha);

    vector<int> x;
    for(int i=0; i<10; i++)
        x.push_back(i);

    vector<int>::const_iterator p = find_if(x.begin(), x.end(), Haha(6)); // create temporary object by conversion constructor to call function object
    cout << *p << endl;
    // how to decide whether it is conversion or operator() -> type(parameter) calls constructor // object(parameter) -> function object
    //Haha(6)(temporary object) -> predicate(*x) -> haha(x[i]) or haha.operator()(x[i]) calling the operator() and return boolean

}