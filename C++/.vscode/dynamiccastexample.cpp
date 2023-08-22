#include <iostream>
using namespace std;

class A{
    public:
        virtual void functionA(){}    
};

class B : public A{

};

int main(){
    A* aPtr = new B;
    B* bptr = dynamic_cast<B*>(aPtr);
}