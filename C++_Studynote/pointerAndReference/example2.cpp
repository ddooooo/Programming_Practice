// inline is a keyword that hints the compiler
// to replace the function call with the real code.
// But it is not guaranteed.
inline int func(int x) {
  return x * x + 2 * x;
}

int main() {
  int a = 10;
  // If compiler will replace the following call for us,
  // the statement will be made as
  // int b = a * a + 2 * a;
  // which has less overhead.
  // Note: Making a function call is expensive.
  int b = func(a);
}
