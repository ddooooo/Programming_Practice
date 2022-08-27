#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

class Add{
    private:
        int data;
    public:
        Add(int i) : data(i) {}
        int operator() (int value) {return value+data;} // return the data + parameter value 
};

class Print {
    private:
        ostream& os;
    public:
        Print(ostream& s) : os(s) {}
        void operator()(int value) {
            os << value;
        }
};

int main() {
    list<int> x;
    for(int i=0; i<5; i++) {
        x.push_back(i);
    }

    vector<int> y(x.size());
    transform(x.begin(), x.end(), y.begin(), Add(10));
    for_each(y.begin(), y.end(), Print(cout));
}

