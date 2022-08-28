#include <iostream>
using namespace std;

class Foo{
    private:
        int b = 10;
    public:
        int modify = 1;
        void set_b(int b) {
            cout << "set b is called" << endl;
            Foo::b = 30;
        }
        int get_b() {
            return b;
        }
};

class A : public Foo {
    public:
        void cannot_modify(int b) const { // const member function -> data member cannot be changed in const member function
            this->b = 10; // can_modify(int b) => compiled as can_modify(const A* this, int b) // pointer to const object
            why = 10; 
            c = new int(10);
            a = new Foo;
        }
        void can_modify2(int b) const {
            a->set_b(b); // why?? -> can_modify(const A* this, int b) { (*this->a)->set_b(b)} => Foo* const is a pointer to const, so a is a const object
            cout << a->get_b() << endl;
            int temp = 10;
            *c = 10; // const c -> hence it is int* const c -> which is const to pointer
            a->modify = 10;
        }
    private:
        int why = 10;
        int* c = &why;
        Foo *a;
};

int main() {
    A a;
    a.can_modify2(100);
    Foo*(a);
    Foo* b = new Foo( test );
}