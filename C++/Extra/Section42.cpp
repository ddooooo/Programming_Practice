#include <iostream>

using namespace std;

template<typename C>
void print2nd(const C& container)
{
    if(container.size() >= 2)
    {
        // C::const_iterator -> dependent name, as the type will be different according to C 
        C::const_iterator iter(container.begin()); 

        ++iter;
        // value -> non-dependent name
        int value = *iter;
        cout << value;

        int x;

        // Compiler won't know C::const_iterator is a type or variable, until the compiler know what type 'C' is
        // so, it could result in operator*(C::const_iterator, x)
        C::const_iterator * x; 

        // To resolve such ambiguity, it is good to put typename at front
        // to tell the compiler C::const_iterator is a type
        typename C::const_iterator* y;
    }
}

// There are exception when typename is not allowed
template <typename T>
class Derived : public Base<T>::Nested // Exception #1: never use typename in the list of base class inhertiance
{
    public:
        explicit Derived(int x) : Base<T>::Nested(x) // Exception #2: neven use typename in the list of member initialization 
        {
            typename Base<T>::Nested temp; // Need to use typename
        }
};

// Using typename and typedef at the sametime
// it looks weird but it is required to use
template <typename IterT>
void workWithIterator(IterT iter)
{
    // It returns the type of a object, which is pointed by IterT type obejct
    // ex) if iter = vector<int>::iterator, then it wil return int
    typedef typename iterator_traits<IterT>::value_type value_type;
}
