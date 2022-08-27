#include <iostream>
using namespace std;

class Number {
  private:
    int number;
  public:
    Number(int number) {     // Constructor
      this->number = number; // Use this pointer to resolve name conflict
      // number refers to parameter number
      // this->number refers to data member number
    }

    // add1
    // - Takes a Number type object using reference (save memory).
    //   The const there prevents us from modifying the received Number object
    // - Returns a Number type object by value.
    //   It creates a copy (temporary object) of the returning object.
    Number add1(const Number& n) {
      number += n.number;
      return *this; // *this refers to the object that we used to call add1
    }

    // add2
    // - Takes a Number type object using reference (save memory).
    //   The const there precvents us from modifying the received Number object
    // - Returns a Number type object by reference.
    //   Note: No temporary object is created.
    Number& add2(const Number& n) {
      number += n.number;
      return *this; // *this refers to the object that we used to call add2
    }

    int get_number() {return number;}
};

int main() {
  Number a(10);
  Number b(20);

  // a is used to call add2, and we get back a.
  // Then a is used to call add1, and we get back a temporary object
  // Finally, we define an object c, and assign the values in temporary object to c
  Number c = a.add2(b).add1(b);
  Number d = a.add1(b).add2(b);
  cout << c.get_number() << endl;
  cout << a.get_number() << endl;
}
