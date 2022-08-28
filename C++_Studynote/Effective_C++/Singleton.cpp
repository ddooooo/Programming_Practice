#include <iostream>

class Singleton
{
    private:
        Singleton() {}
    public:
        Singleton& getInstance()
        {
            static Singleton instance;
            return instance;
        }
};

class A
{
    public:
        A()
        {
            Singleton singleton = singleton.getInstance(); 
        }
};