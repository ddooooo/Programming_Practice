//Temporary object is deleted very soon//
//Look at page11 in move/reference ppt

/***********************************/
//Similarities with const lvalue reference and rvalue reference
//Both can be bounded to a temporary object/value
//Both are reference -> must be initialized 

//Difference
//const T& cannot be modified but T&& can be modified
//const T& can take almost any arguments --> const rvalue/lvalue, temporary value/object, and even rvalue reference
//T&& can only take temporary value/object
//If you have both f(const T&) and f(T&&) and input argument is temporary, then f(T&&) will be called - the best choice
/*********************************/

/**************Move Semantics*****************/
//Move the resources
//when deleting the temp object that contains pointer that points to array
//make a copy(haha) of the temp except the pointer
//make haha points at temporary's pointer array
//then delete temp => will save resources
//


/**********************move function : std::move(named object)*****************/ //need to iostream!
//Give named object to parameter, and return unnamed object(same object) -> static casting
//Use it, when I want to call move assignment or constructor
//Then Returned object won't have resources


#include <iostream>
using namespace std;

class A {
    private:
        int* p = nullptr;
        int a;
        int b{1};
    public:
        A() {}
        A(int a) { A::p = new int(10);  cout << "Conversion" << endl;}
        A(const A& a) { cout << "copy" << endl;}
        A(A&& a): p(a.p) {a.p = nullptr; cout << "Move" << endl;} // **Move constructor**, only call this constructor with *new object(unnamed)*
        A f(A&& a) { cout << "Return by value hence it will create a temp box, so return a or move(a) wont matter" << endl; return a;}
        A& g(A&& a) { cout << "Return by referece, so it returns lvalue type, therefore, return a" << endl; return a;}
        A&& h(A&& a) { cout << "Return by rvalue (unnamed object), hence it needs to return move(a)" << endl; return move(a);}
        A& i(A& a) {
            return h(move(a)); // return type is A& while actual type of returned object is h(move(a))
        }
        void func(int d) { this->a{d}; }
        ~A() {}
};

class B {
    private:
        A* a;
    public:
        B() { a = new A();}
        B(int a) {}
        const A& get_a() const { return *a;}
        void set_a(A* a1) const { a = new A(1); }
};

A haha(const A& a) {
    return a; //returned by value will create a temporary object
}

A haha2() {
    A a;
    return a; // move constructor will be called -> but why named object calls move constructor ??
              //-> because 'a' will be deleted soon, A temp(a), chosen by c++ compiler; 
}

int square(int x) {return x*x;}

int main() {
    A test;
    B test2;
    test2.get_a();
    const A& aa = 10; //it will call temp(10) that is temporary object, 
                      //temp(10) will call conversion constructor, 
                      //and temporary object can be bounded to const reference
                      // the temporary object will be kept until out of scope(end of main)
    A aa2 = 10; // without getting temporary object, the most complier will just call conversion constructor 
                // or it will call copy constructor or move constructor(if it is implemented)
    A aRet = haha(10); //Pass 10 to conversion constructor and get the temporary object 
                       //haha(10) will create another temp object and call copy constructor 
                       // or move constructor(if it is implemented)
    const B& haha2 = B();//Create an temp object of type A by calling default constructor 
                         //Const reference can be bounded to either named and unnamed object
                         //Cannot modify the temporary object
                         //lvalue reference
    B&& hehe = B(); // '&&' can only be bounded to unnamed object(temporary object)
                    // Can modify the temporary object
                    // Rvalue reference
    B& b = hehe; // Valid, as the temp object is named object
    B&& no = hehe; // Invalid, as Rvalue reference is *only* for unnamed object
    B&& no2; // Invalid, as Rvalue reference must be initialized!
    const B& yes = hehe;
    B&& hehe1 = 10; // call conversion constructor
    const B&& hehe2 = B(); //Similar to 'const B&' 
    //Unnamed Object
    //1. Use new -> int* a = new int;
    //2. Use && -> T&& a = 10 -> Rvalue reference
    //3. Use const reference -> const T& a = 10;
    //Even function that returns primitive type by value will still create a temporary box
    
    B&& no3 = B();
    B&& no4 = no3;


    /************************************/
    int a = 3;
    int aa = 4;
    int&& ok = 5; // the integer type temporary(unnamed) box that contains 5 will be created, and 'ok' will be assigned to that temp box
    const int& c = 5; // create a temporary box of int type
    int&& d = square(3); // square(3) will return by value that creates a temporary box
    int&& e = a + c + d; // (a+c) will first create a temporary box and ( (a+c) + d ) will create a temporary box
    d = e = 10; // (e=10) first and then (d = e)
    int& no3 = a; 
    no3 = aa; // whence you bound a nick name, cannot take it back(change)
    int* strange = 1;
}
//Compiler-generated Member FunctionS//
//1. default constructor
//2. default copy constructor (memberwise copy)
//3. default assignment operator (memberwise copy)
//4. move constructor
//5. move assignment operator
//6. default destructor
