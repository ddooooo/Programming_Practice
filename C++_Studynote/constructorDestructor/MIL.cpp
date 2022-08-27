#include <iostream>
using namespace std;

//5 different Usages of MIL 
int global = 5;
// 1. Use MIL to resolve name conflict.
class MIL1 {
    private:
        int a;
        int b;
    public:
        MIL1(int a, int b) : a(a), b(b)  {}
};

// 2. Use MIL to choose which constructor to call for the construction of object data member.
class MIL2 {
    private:
        MIL1 a;
    public:
        MIL2(int a, int b): a(a, b) {}
};

// 3. Use MIL to initialize constant data members and reference data members.
class MIL3 {
    private:
        const int const_m = 8;
        int& ref_m = global;
    public:
        MIL3(int a, int& b) : const_m(a), ref_m(b) {} // Value of const_m and ref_m will be the one that is assigned by MIL not by data members
};

// 4. Use MIL to call another constructor of the same class, i.e. delegating constructor.
class MIL4 {
    private:
        int a;
        int b;
    public:
        MIL4(int a, int b) : a(a), b(b) {}
        MIL4(): MIL4(a, b) {} // Other than MIL4(a, b), no other MIL should be added
};

// 5. Use MIL to call parent class’s constructor to initialize data members that we grabbed from the parent class.
class MIL5 : public MIL4 {
    private:
        int a;
        int b;
    public:
        MIL5() : MIL4(5,4), a(a), b(b) {}
};

int main() {
    int aa = 3;
    int& bb = aa;
    MIL1 a(1, 2);
    MIL2 b(3, 4);
    MIL3 c(6, bb);
    MIL4 d;
    MIL5 e;

}