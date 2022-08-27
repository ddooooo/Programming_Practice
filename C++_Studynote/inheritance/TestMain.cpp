#include <iostream>
#include <typeinfo>
using namespace std; 


class A {
    public:
        int x = 101;
        virtual void func() {
            cout << "Function A" << endl;
        }
};

class B : public A {
    public:
        int y = 100;
        virtual void func() override { // it checks whether the code overrides correctly!
            cout << "Function B" << endl;
        }
        void gunc() {
            cout << "Gunction B" << endl;
        }
};

class dooQ : public B {
    public:
        virtual void func() const{ //if you put 'const' it is not overriding 
            cout << "Function C" << endl;
        }
        void gunc() override { // c++ thinks if there is no virtual function, then it is not overriding
            cout << "Gunction dooQ" << endl; 
        }
};

int main() {
    A* p2 = new B; // Parents can only points to its child, p is **A** type!!!,  and it points at B constructor
    B* no = new B; // It is an error when child points at its parent, no is **B** type!!
    B* p3 = new dooQ; //p3 is ***B*** type!!!!
    //p2->y; // p can only access to its own member data and member function(if there is no virtual function)
    no->x; // 'no' can access to its parent's data member!
    dooQ* dq = new dooQ;
    dq->x; dq->y; // dq can access its ancestor's data member 
    A a;
    B b;
    A& yes = a;
    A& yes2 = b; // parent can bound to child
    B& yes3 = b;
    //B& no2 = a; // Child cannot bound to parent 
    cout << typeid(*p2).name() << typeid(A).name() << endl; //must have one virtual function in base class
    p2->A::func(); //during complition time or Before runtime we can know which function to be called - static binding
    p2->func(); // during runtime/execution time - Dynamic binding (virtual function)
    //p->gunc(); // error as p is A type!!! 
    B* q = dynamic_cast<B*>(p2); // convert p (A type pointer) to B type pointer // might not be working // must have virtual function in base class
    dooQ* s = dynamic_cast<dooQ*>(p2); // it will not work as p is not pointing to dooQ object // returns nullptr
    q->gunc();
    B* p1 = new dooQ;
    cout << typeid(*p1).name() << endl; // typeid returns object // checks the type during runtime -> dynamic binding
    p1->func();
    p1->B::func();
    p1->A::func();
    //compilation error p1->dooQ::func();
    if(typeid(*p) == typeid(A)) //typeid also accept object
        cout << "AA" << endl;
    return 0;
}