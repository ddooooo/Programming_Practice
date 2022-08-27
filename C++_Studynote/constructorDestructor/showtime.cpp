#include <iostream>
using namespace std;

class Word {
  public:
    Word() { cout << "Default constructor" << endl; }
    Word(const Word& haha) { cout << "copy constructor" << endl; }
    Word to_upper_case() {
      Word x(*this);
      return x;
    }
    ~Word(){
      cout << "Destructor" << endl;
    }
};

int main() {
  Word desmond;
  Word brian = desmond.to_upper_case(); // create a object x by copy constructor, and create a temp object to copy all from x, and then copy x to object brian by copy constructor
}
