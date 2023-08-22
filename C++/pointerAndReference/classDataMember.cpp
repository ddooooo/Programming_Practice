class Haha {
  private:
    int k = 1; // :)  Data member can be initialized using =
    int l(20); // >.< Data member cannot be initialized using ()
    int m{30}; // :)  Data member can be initialized using {}
}; // Note: Initializing data members when they are declared only works
   // in C++11 or newer, i.e. older version of C++ doesn't allow this.

int main() {
  // For local variables, all three symbols, i.e. =, (), {} can be used.
  int a = 1;   // :)
  int b {1};   // :)
  int c(1);    // :D

  // The following lines is illegal. Since compiler expects us to assign
  // a value in type that match with d, IF WE DO INITIALIZATION USING {}.
  // As 2.3 is double type, it doesn't match with the type of d.
  // So, error occurs.
  int d {2.3}; // :(
}
