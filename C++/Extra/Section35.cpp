#include <iostream>
#include <functional>

using namespace std;
using namespace std::placeholders;

class Base; // 전방선언(Declaration)

class ClassCalcFunctor
{
    public:
        ClassCalcFunctor(int a) : a(a) {}
        int classCalcFunc(const Base&) 
        {
            cout << "classCalcFunc called!" << endl;
            return a;
        }

    private:
        int a;
};

struct StrucCalcFunctor
{
    public:
        StrucCalcFunctor(int a) : a(a) {}
        int operator() (const Base&) const 
        {
            cout << "StrucCalcFunctor called!" << endl;
            return a;
        }
    
    private:
        int a;
};

int DefaultCalcFunc(const Base&)
{
    cout << "DefaultCalcFunc called!" << endl;
    return 10;
}

float FloatCalcFunc(const Base&)
{
    cout << "FloatCalcFunction called!" << endl;
    return 20.0;
}

class Base
{
    public:
        // Using Point to Function with the name 'ValueCalcFunc1', can only point to the same return and parameter type
        // But this pointer can only point to specific function with return type 'int' and parameter type 'Base'
        typedef int( *ValueCalcFunc1) (const Base&);
        
        // Using tr1::function
        typedef function<int (const Base&)> ValueCalcFunc2;

        //typedef function<int (const Base&)> ValueCalcFunc;

        Base(ValueCalcFunc1 pf1 = DefaultCalcFunc, ValueCalcFunc2 pf2 = DefaultCalcFunc) 
                : value(10), m_valueCalcFunc1(pf1), m_valueCalcFunc2(pf2)
        {}

        Base(ValueCalcFunc2 a) : m_valueCalcFunc2(a)
        {}

        Base(int a) : value(a)
        {}

        virtual int getValue() const
        {
            return value; // 비순수 가상함수는 기본 클래스에서 기본 알고리즘이 적용됨
        }

        int getValue2() const
        {
            // Non-virtual interface function
            // Wrapper
            int result = calValue();
            return result;
        }

        int getValue3() const
        {
            int a = m_valueCalcFunc1(*this);
            int b = m_valueCalcFunc2(*this);
            return a+b;
        }

    private:
        ValueCalcFunc1 m_valueCalcFunc1;
        ValueCalcFunc2 m_valueCalcFunc2;
        int value;
        virtual int calValue() const
        {
            cout << "Calvalue in Base class" << endl;
            return value; // 파생 클래스에서 이 함수를 오버라이드 할 수 있음
        }
};

class Derived : public Base
{
    public:
        Derived(int a) : value(a) 
        {}

    private:
        int value;
        virtual int calValue() const
        {
            cout << "Calvalue in Derived class" << endl;
            return value;
        }
};

int main()
{
    Base* pb = new Derived(30);
    cout << pb->getValue2() << endl;

    cout << endl;

    Base b;
    cout << b.getValue3() << endl;

    cout << endl;
    
    // See the power of tr1::function
    Base b2(DefaultCalcFunc, FloatCalcFunc);
    cout << b2.getValue3() << endl;

    cout << endl;
    StrucCalcFunctor h(10);
    Base b3(DefaultCalcFunc, h);
    cout << b3.getValue3() << endl;

    cout << endl;
    ClassCalcFunctor c(200);
    auto ptr_to_mem_func = mem_fn(&ClassCalcFunctor::classCalcFunc);
    auto mem_func = &ClassCalcFunctor::classCalcFunc; // Gives error
    auto f1 = bind(ptr_to_mem_func, ref(c), _1);
    Base b4(DefaultCalcFunc, f1);
    cout << b4.getValue3() << endl;
    //HelpCalcFunctor h(100);
}