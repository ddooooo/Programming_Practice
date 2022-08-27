int my_max(int a, int b) {
    return (a>b) ? a : b;
}
int my_min(int a, int b) {
    return (a>b) ? b : a;
}
int my_add(int a, int b) {
    return a+b;
}
int my_sub(int a, int b) {
    return a-b;
}

int func(int (*a) (int, int) ){
    int value = a(10, 20);
    return value;
}

int main() {
    int(*haha) (int, int) = my_max; // variable name haha to points at the function with two integer parameter(my_max)
    // overloading it not working, it has to be exactly same type -> const(will be emailed)
    int result = haha(1,2); // calls my_max -> my_max(1, 2), right before leave main(), it will be deleted(local variable)
    int(*hehe) (int, int); // type of hehe -> int(*)(int, int) // but int(*)(int, int) hehe -> not possible // it points at garbage
    hehe = &my_max; // it works, but need to dereference to call the function
    int result1 = (*haha) (1,2);
    //delete haha; ->  cannot new the function( haha = new my_max  -> error)/ hence it is not possible
    int a = 1;
    int(*b) (int, int) = (a == 1) ? my_max : my_min; // can only points to function with two integer parameter and return type
    cout << b(5,8) << endl; 

    int(*c[]) (int a, int b) = {my_max, my_min, my_add, my_sub}; // array of the function pointers -> 4 function pointers in array
    for(int i=0; i<4; i++) {
        cout << c[i](1,2) << endl;
    }

    void (*d) (int, int) = [] (int x, int y) { cout << (x+y) << endl;}; // ramba function to define function with no name, use function pointer to give a name to ramda function 
    d(12, 12);
    d(a, b(10, 20));

    int (*sum) (int, int) = [] (int x, int y) { return x+y;};
    func(sum);
    func(d);
}