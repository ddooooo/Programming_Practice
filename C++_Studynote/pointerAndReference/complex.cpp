#include <iostream>
using namespace std;

int main() {
    int a = 10;
    const int b = 30;
    int* p = &a;
    p = &b; // int* cannot accept const int variable
    const int* pc = &a;
    pc = &b;
    const int* const& strange = &a;
    strange = &b;
    *strange = 30;

}