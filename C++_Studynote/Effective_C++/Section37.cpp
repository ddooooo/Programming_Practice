#include <iostream>

using namespace std;

class Base
{
    public:
    enum ShapeColor {Red, Green, Blue};
    
    virtual void draw(ShapeColor color = Red) const = 0;

    private:
    // Solution for virtual function with default parameter is to use non-virtual interface
};

class Derived1 : public Base
{
    public:
    virtual void draw(ShapeColor color = Green) const 
    {
        cout << "Draw in derived1: " << color << endl;
    }
};

class Derived2 : public Base
{
    public:
    virtual void draw(ShapeColor color) const
    {
        cout << "Draw in derived2: " << color << endl;
    }
};

int main()
{
    Base* bp;
    Base* dp1 = new Derived1;
    Base* dp2 = new Derived2;

    // dp1, which is dynamically binding to Derived1, will call draw in Derived1 class
    // but the default parameter, which is static binding, will be same as parameter in draw function in base class
    // So, it is bad to change default parameter of virtual function
    dp1->draw(); 
    dp2->draw();
}