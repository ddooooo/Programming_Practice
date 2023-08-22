#include <iostream>
using namespace std;

template <typename T>
void f(T x, T y) {
    cout << "Template" << endl;
}

void f(int x, int y) {
    cout << "non template " << endl;
}

int main() {
    f(4, 5); // call non-template
    f(4, 'a'); //call non-template
    f('a', 'a'); // call template
}