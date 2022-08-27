#include <iostream>
using namespace std;

/***********************/
//friends function can accesss all data members both public and non-public
//it is not symmetric -> A is B's friend, does not make B is A' freinds
//
class A{
    private:
        int a;
        friend class B; // B must be declared
        friend class Hehe; // works eventhough it is not defined 
        friend void globalHaha(int a);
        //friend void B::haha();
    public:
        A() {
            B b;
            b.a; //-> A is B's friend but B is not A's friend
        }
        void func_A() {
            cout << "it function in A" << endl;
        }
};

void globalHaha(int a) {
    A obj;
    obj.a = 2;
}

class B{
    private:
        int a;
    public:
        B() {}
        B(const B& b) {}
        void haha(){
            A obj;
            obj.a = 20; 
        }
};


class C : public B{
    private:
        int a;
    public:
        C() {
            A no;
            no.a; // friend is no inherited
        }
};


int main() {
    B b;
    b.haha();
}