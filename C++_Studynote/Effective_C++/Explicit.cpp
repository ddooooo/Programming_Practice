#include <iostream>

class A
{
    public:
        explicit A(int a) : a(a)
        {}
    private:
        int a;
};

int main() 
{
    A a = 10; // call copy constructor, but gives error, because constructor is specifically defined as 'explicit'
    A b = A(10); // call copy constructor
    
}