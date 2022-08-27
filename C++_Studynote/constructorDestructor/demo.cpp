class A {
  private:
    int a;
  public:
    void func() {
      // this pointer is defined by C++ compiler.
      // It points at the object we used to call the function.
      // In this case, obj // func(A* this) or if const func(cont A* this)
      this->a = 10;
    }
};

int main() {
  A obj;
  obj.func();
}
