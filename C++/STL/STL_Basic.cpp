// 25/04/2012 //
        // Type of Container//

// Deque (Double-ended queue)
//-> Not stored continguously
//-> the storage of a deque automatically expanded and contracted
//-> takes O(1) to removed and add -> from both end and front -> it is very fast

//Vector (1D array)
//-> random access O(1)
//-> Add/remove -> O(1) at the end, O(n) in front or middle

//List (doubly-linked list)
//-> Access the item in the middle -> O(n)
//-> Access the itme at front/end => O(1)
//-> Add/Remove -> O(1) at any position

//Function for Sequence Container
// 1. front() -> get the first element
// 2. back() -> get the Last element
// 3. Element access for vector and deque -> [](subscript Operator)
// 4. push_back() -> Append element at the last
// 5. pop_back() -> Remove the last element
// 6. push_front() for list and queue-> Insert element at the front
// 7. pop_front() for list and queue-> Remove the first element
// 8. insert(p, x) -> insert an element x at position p
// 9. erase(p) -> Remove an element at position p
// 10. clear() -> Erase all elements 
// 11. size and capacity is different
// 12. resize() -> change the number of element -> fill the container with default value to expanded position
// 13. capacity -> the size of the container
// ex) (1,2,8) resize(5) -> (1,2,8,0,0,0, , , ) -> size() returns 6 -> capacity() return 8 including all blanck box
// NO control of capacity of vector

/////////////Container Adaptors//
//Stack -> Last in First out
//Queue -> First in First out
#include <iostream>
#include <deque>
using namespace std;
#include <list>
typedef list<string> LISTSTR;

//Simplified STL Stack 
template<typename T, typename Sequence = deque<T> > // typename Sequence = deque<T> -> deque<T> as default container to store the data
class stack {
    protected:
        Sequence c;
    
    public:
        typedef typename Sequence::value_type   value_type; // Rename 'Sequence::value_type' as value_type for shortening word
        typedef typename Sequence::reference    reference; 
        typedef typename Sequence::const_reference  const_reference;
        typedef typename Sequence::size_type    size_type;

        explicit stack(const Sequence& _c = Sequence()) : c(_c) {}
        bool empty() const { return c.empty();}
};

int main() {
    LISTSTR test2(4, "Four");
    LISTSTR test3(3, "Three"); // the size of the list is 3, the string that will be inserted is "Three", hence it inserts "Three" for 3 times
    LISTSTR test4(++test3.begin(), test3.end()); // -> insert from test3.begin() + 1 to test3.end()
    LISTSTR test5(++test2.begin(), test2.end());
    LISTSTR::iterator i;

    cout << *(--test3.end()) << endl;




    for (i =  test5.begin(); i != test5.end(); ++i)
        cout << " " << *i << endl;

}