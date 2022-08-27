#include <iostream>
using namespace std;

class Foo{
    public:
        Foo() { cout << "A"; }
        ~Foo() { cout << "B"; }
        Foo(const Foo& x) { cout << "C"; *this = x; }
        Foo(Foo&& x) { cout << "D"; *this = x; }
        const Foo& operator=(const Foo& x) { cout << "E"; return *this; }
        const Foo& operator=(Foo&& x) { cout << "F"; return *this; }
};

int main() {
    Foo obj;
    cout << endl;
    Foo obj2(move(obj));
    cout << "end of main" << endl;
}