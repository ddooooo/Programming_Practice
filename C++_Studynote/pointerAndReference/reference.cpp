#include <iostream>
using namespace std;

int main() {
    int a = 10;
    int& ref = a;
    int b = 30;
    ref = b;
    ref += 10;
    cout << ref << endl;
}