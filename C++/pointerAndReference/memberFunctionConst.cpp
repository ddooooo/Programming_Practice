#include <iostream>
using namespace std;

int c;        // Global variable c

class Haha {
  private:
    int a;    // Data member a
  public:
    void func() const {
      int b;  // Local variable b
	  // The line below causes compilation error.
	  // As there is a const after (), no data member can be modified.
      //a = 20;
	  // But the const after () has nothing to do about local variable.
	  // So the line below is valid.
      b = 30;
	  // Samething. The const after () has nothing to do about global variable.
	  // So the line below is valid.
      c = 40;
      a=30;
    }
    inline void yes() {}
    const void gunc() {
      a = 20;
    } 

    void haha();
};

inline void Haha::haha() {
  cout << "Inline function!" << endl;
}

int main() {
  Haha desmond;
  desmond.func();
  desmond.haha();
}
