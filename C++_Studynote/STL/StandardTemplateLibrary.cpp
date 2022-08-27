#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class A {
    public:
        class B {
            // class B is a class in object A,  not object 
        };
};

/*template <class Iterator, class T>
Iterator find(Iterator begin, Iterator end, const T& value) {
    while(begin != end && *begin != value) {
        ++begin;
    }

    return begin;
}*/

int haha(int a, double b) {
    return 1;
}


class C {
    private:
        int a;
    public:
        //Function Object must have at least operator()
        C(int a) : a(a) {}
        int operator()(int v) {
            return v + a;
        }
};

template <typename T> //Class template
class Dada {
    private:
        int haha;
        template <typename S>
        freind ostream& operator<<(ostream& os, const Dada<S>& x);

};

template <typename T> // Function Template that will work on any class that is created from class template (Data<T>& a)
ostream& operator<<(ostream& os, const Dada<T>& a) {
    return os << a.haha << endl;
}

/* STL algorithm - find() 
template <class Iterator, class T>   
Iterator find(Iterator first, Iterator last, const T& value) {
    
    while (first != last && *first != value)
        ++first;
    
    return first;
}

*/

int main() {
    vector<int> v(10); // 10 means the size of the container(number of elements/not capacity)
    for(int i=0; i<v.size(); ++i){
        cout << v[i];// print 0
    }
    cout << endl;
    v[0] = 10;
    v[1] = 20;
    v.resize(2);
    for(int i=0; i<v.size(); ++i){
        cout << v[i];
    }

    cout << endl;
    cout << "Using pointer to traverse the Normal Array" << endl;
    const int LENGTH = 5;
    int x[LENGTH];

    for (int j = 0; j < LENGTH; ++j)
        x[j] = j;

    const int* x_end = &x[LENGTH]; // points to an element beyond the array
    for(const int* p = x; p != x_end; ++p)
        cout << *p << endl;
    cout << endl;

    // const_iterator -> pointer to const, it can be modified but the thing that is pointed by it cannot be changed 
    //iterator is a class that is defined in the vector<> class template
    //iterator is to pointer to point at elements in vector, v.begin() returns address of the first box, v.end() returns the address of the after last element of vector
    cout << "Using Iterator pointer to traverse a Sequence Container" << endl;
    vector<int>::iterator it;
    for( it = v.begin(); it<v.end(); it++) { // 
        cout << *it << endl; // dereference to get the data
    } 

    //find() -> if the find() could not FIND an element in container, it will return v.end()
    vector<int>::iterator p = find(v.begin(), v.end(), 10);
    if(p != v.end()){
        cout << "Found!" << *p << endl;
    }else if( ++p == v.end()) {
        cout << "Found as the last element" << endl;
    }else {
        cout << "NOT FOUND!!" << endl;
    } 

    //function pointer
    int (*fp) (int, double) = haha;

    cout << fp(1, 1.2) << endl;

    C obj(10);
    int result = obj(2);
    cout << result << endl;
}