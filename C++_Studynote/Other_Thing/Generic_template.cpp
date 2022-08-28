#include <iostream>
using namespace std;
#include <cstring>
#include <typeinfo>

// ************Generic Programming*****************//
// 1. Only one version of code that works for many different types of objects!
// 2. It can be used to create *function template* and *class template* 

template <typename T> //<class T> this is not prefered
inline const T& larger(const T& a, const T& b) { // no parameter woud cause warning but large<type>() can solve problem when using the funtion
    return (a>b) ? a : b; // make sure it work with any data
}

template <typename T1, typename T2>
inline const T1& larger(const T1& a, const T2& b) {
    return (a>b) ? a : b;
}
//--> when calling larger(const T1& a, const T2& b) 
//ex1) larger(4, 5.5) => int larger(int, double), but output 5.5(double)
//but the return type is int but the type of value that will be returned is 5.5 which is double type
//since there is a type mismatch, compiler will create a temp box with int type and copy 5.5 into the temp box,
//const int(T1)& can be bouded to temp box, but the temp box will be deleted as soon as compiler leaves larger(), hence it creates a error 
/**************************************************/
//ex2) larger(5.5, 4) => double larger(double, int) => will return 5.5 hence compiler will not create a temporary box, and just return 5.5

template <> // not necessary as it is just a regular function but for readablity
const char* const& larger(const char* const& a, const char* const& b) {
    cout << "special case: ";
    return (strcmp(a, b) < 0 ? b : a);
}


//class template should be in one file not two file one in .h and one in .cpp
template <typename T, int haha> // int haha is constant variable
class Hehe {
    public:
        void func() {
            //haha = 10; // cause error since haha is constant variable
        }
};

template <typename T, const int N> // can put const variable
int f(T (&x) [N]) { // &x is a reference to array int (&x) [5] = arr (int arr[5]) rather use pointer as it looks weird
    return N;
}

template <typename T>
class A {
    
};

template <typename T>
class B {
    public:
        A<T>* func() {
            A<T>* p;
            return p;
        }
};

class Haha {
    private:
        int a;
    public:
        Haha(int a) : a(a) {}
        Haha operator-(const Haha& h){ 
            return Haha(a - h.a);
        } 
        const Haha& operator+=(const Haha& h) { // return vector type object // if put return type const it cannot be changed and to prevent change to order ex (x+ y)+z
            a += h.a;
            return *this;
        }
        friend Haha operator+(const Haha&, const Haha&); // allow to access to all data members Private
        friend ostream& operator<<(ostream&, const Haha&);
        Haha operator++(int) {
            Haha temp(a); // post increment which returns temporary object 
            a++;
            return temp; // returns temporary object
        }
};

Haha operator+(const Haha& x, const Haha& y) {  //global function is better than member function, 
    return Haha(x.a + y.a); // return by temp value not reference
}
// return os is existing stuff from parameter  
//never put const // if change to void it will only cout one
ostream& operator<<(ostream& os, const Haha& h) {
    return os << h.a;
};


//**********************Equal Operator(=) Overloading**************************//
class MyArray {
    private:
        int* p;
        int size;
    public:
        MyArray(int size) : size(size) {
            p = new int[size];
        }
        MyArray(const MyArray& arr) {
            size = arr.size;
            p = new int[size];
            for(int i=0; i<size; ++i){
                p[i] = arr.p[i];
            }

            /***********/
            //using equal operator to make copy constructor
            //p = nullptr -> very important!~! -> after calling equal operator, it will delete p, but if p is nullptr, deleting nullptr will cause problem unless the class already has initialize pointer as nullptr
            //*this = arr; => calling equal operator for copying all element
        }
        ~MyArray() {
            delete [] p;
        }
        const MyArray& operator=(const MyArray& arr) {
            if(this != &arr) { // to check whether left and right side is same
                delete [] p;
                p = new int[arr.size];
                for(int i=0; i<arr.size; ++i)
                    p[i] = arr.p[i];
                size = arr.size;
            }
            return *this;
        } 
};

/*********************************************************/
//Template function and class can also have nontype parameter, type variables but it is constant variable cannot be redeclared in the class or function

template<double T> //Floating numbers are not allowed!! 
double funct() {
    return T;
}

template<MyArray T> //class type object are not allowed!!
MyArray funct4() {
    return T;
}

template<int T>
int funct2() {
    return T;
}

template<int x>
int funct2_2() {
    x = 30;
    return x;
}

template <typename T>
funct3<T>(T x) {
    return x;
} // this is invalid function temmplate

template <typename T>
T funct4(T x) {
    return x;
}

template <typename T>
T* funct5() {
    return new T;
}

int main() {
    funct5<int>();
    funct5();
    int resultSame = larger(2, 3); // make use of generated(instantiation) function not redefinition / implicitly instantiation / c++ complier will guess the type T by refering to parameter that is passed by function
    int result = larger(1, 2); // generate T as integer // generate the function during complilation
    int result2 = larger(1.0, 2.3); // generate T as double but result will be integer
    int result3 = larger<double>(1.0, 2); // same as <static_cast> <dynamic_cast> *function template* explicitly instantiation
    // error int result = larger(1.0, 2); // Different type 
    //int result4 = larger('A', 50); //error
    larger(4, 5.5); // convert a into double create a temp double box that has 4.0  and create another int temp box that has 5 and return it as return type is deleted(before leaving the function) as it is temp so it will get warning
    larger(5.5, 4); //it seems it does not get warning but ? a: b will always create temp box // solution return it by T1 not T1&(reference) or use statement
    const char* m = "microsoft";
    const char* n = "apple";
    larger(m, n); // not good template function for char pointer so it needs template specialization!

    B<int> obj;
    obj.func(); // it may or may not create A object depends on complier

    Haha obj1(10);
    Haha obj2(20);
    //Haha obj5(30);

    Haha obj3 = obj1 + obj2; // call copy constructor defined by c++  // when the function is defined as the member function it will be like "obj1.operator+(obj2)"
    //Haha obj3 = operator+(obj1, obj2) it works but no point of overloading the operator+ function
    operator+(1, 2); //it works
    //cout << operator+(1, 2) << endl; error
    // *******when it is calling member fucntion********** but if global function works on both -> operator+(obj1, obj2)
    // 1. Haha obj4 = 1 - obj1 error as 1.operator-(obj1) 
    // 2. Haha obj4 = obj1 - 1 is works as obj1.operator-(1) (1 -> conversion construrction) and killed at the end of the global function
    // cout << obj1; is not available as cout only accept primitive value
    // cout is ostream type object

    cout << obj1 << 10; // call two function one for defined by me and one for c++
    // when operator<<() is global function operator<<(cout, obj1)
    // when it is member function cout.operator<<(obj1) it shoud be define as ostream class
    // obj1 << cout -> obj1.operator<<(cout)

    obj1 += obj2 += obj3; // right to left (=>)

    int a = 10;
    ++a = 20; // it works as ++a returns variable a and assigned 20 to a. pre increment
    a++ = 20; //not working it returns value of a before increment(ex, a=10) post increment

    int a = funct2<10>();
}