#include <iostream>
using namespace std;

int a = 10;

int& test(int num)
{
    a = num;

    return a;
}

int main() {
    
    
    int* ref = &test(30);

    *ref = 50;

    cout << a << endl;
}