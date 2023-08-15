#include <iostream>
using namespace std;

// ***************Abstract class***************//
// an object of *Abstract class* cannot be created never! - but pointer that points to abstract class  and reference that bounds to abstract class can be declared
// Its derived class must must implement the pure virtual functions, otherwise it will be like Abstract class


class Car {
    public:
        virtual int getSpeed() const = 0; // need to have virtual to override, pure virtual function //put this function because it is essential to the class but dont know how to implement
        virtual int getSpeed() = 0;
        // Car func1(int a) { 
        //     getSpeed();
        //     Car();
        // } // cannot return by value

        int func2(Car a) {} // If parameter has type of abstract class, it is error
};

// Use of getSpeed in class Car
int Car::getSpeed() const{ //even implement later, still not able to define a car object
    return 10;
}

class BMW1000 final : public Car { // final -> no class can inhertiance this class
    public:  // virtual can be obmitted but encourage to put for readable code & no more overiding of this function with final , and should be virtual function
        virtual int getSpeed() const final{ // if Not implement this function, just inheritance virtual function from class Car
            return Car::getSpeed() + 100; // final -> no more override in other derived class
        }

        virtual int getSpeed() {
            return 1000;
        } // if the function is not implemented in derived class, then this class is also a abstract class!!
};

int main() {
    //Car c;
    Car* p; // pointer and reference to an abstract class is 

    BMW1000 b; //if no virtual function, it wont call BMW1000 class, then it will be error
    Car& d = b; 
}

