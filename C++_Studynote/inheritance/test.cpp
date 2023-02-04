#include<iostream>
using namespace std;

class X 
{
  public:
    virtual void func()
    {
      cout << "Hello from x" << endl;
    }

    int x;
};

class Y : public X
{
  public:
    void func()
    {
      cout << "Hello from y" << endl;
    }
};

int main()
{
    // X a = { 10 };
    // X b = a;
    // cout << a.x << " " << b.x;
    // return 0;

  X* a = new Y();
  a->func();

  return 0;

}