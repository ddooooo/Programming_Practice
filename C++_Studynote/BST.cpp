#include <iostream>
using namespace std;

//Binary Search Tree -> it is the binary tree but all nodes in the left are smaller than root node and all nodes in the right are greater than root nodes 
//          6
//        2   8
//       1 4
//Recursive Function
//->Any subtree of BST is BST
//the worst BST -> linked list just one line
//the left linked list -> bigger number to smaller number -> descending order
//the right linked list -> smaller number to bigger number -> ascending order
//BST search => very efficient => start from root
//Given data is smaller than key -> need to serach only left side of BST 
//Given data is greater than key -> need to search only right side of BST
//If the given data is not in BST -> return nullptr
template <typename T> //why class template => need to store different type
class BST {
    private: //BSTnode is NOT data member for BST, just define struct inside of BST
        struct BSTnode { //only access in class BST, no outsider will care about the nodes
            T value;
            BST left;   // BSTnode has 3 data members
            BST right;
            BSTnode(const T& x) : value(x){} // conversion constructor to store a data in BSTnode
            BSTnode(const BSTnode& node) = default; // copy constructor and it is memberwise copy and default as it is just object that is copied
            ~BSTnode() {
                cout << "delete: " << value << endl; // Remove BST right -> BST left -> T value (first in last out)
            }
        };
        BSTnode* root = nullptr; //one data member only, BST object will use this to point at BSTnode that holds the data 'key' and BST Left, Right

    public:
        BST() = default;
        ~BST() {
            delete root; // Recursive(delete BST <-> delete BSTnode) when the BST is deleted 
                         //=> call desturctor of BST that deletes root(BSTnode) 
                         //=> call BSTnode destructor to kill all data members of BSTnode 
                         //=> kill BST right(Last in First out) 
                         //=> will call BST right's destructor 
                         //=> delete BSTnode* root(right side)
                         //=> will call destructor of BSTnode(rightside) => until reaches nullptr (the leaf) 
                         //=> do the samethig for BST left (calling BST left's destructor)
                         //=> lastly delete value
        }

        BST(BST& bst) {  //shallow BST copy
            root = bst.root;
            bst.root = nullptr;
        }

        BST(const BST& bst) {
            if(bst.is_empty()){
                return;
            }

            root = new BSTnode(*bst.root); //recursive 
                                           //first it calls copy constructor of BSTnode to copy root and 
                                           //value will copied 
                                           //then the copy constructor of BST of left and right will be called 
                                           //so on by recursion
        }

        bool is_empty() const {
            return root == nullptr;
        }

        void print(int depth = 0) const;
        bool contains(const T&) const;
        const T& find_max() const;
        const T& find_min() const;
        void insert(const T&);
        void remove(const T&);
};

template <typename T>
void BST<T>::print(int depth) const {
    //To do!
    
    if(depth = 0) {
        cout << root->value << endl;
    }

    if(root->left) {
        root->left.print(depth-1);
    }
    if(root->right) {
        root->rigth.print(depth-1);
    }
}

template <typename T>
const T& BST<T>::find_min() const {
    //To do! // can do it with recursion
    if(root->left == nullptr)
        return root->value;
    
    root->left.find_min();
}

template <typename T>
const T& BST<T>::find_max() const {
    //To do! // can do it with recursion // keep going right
    if(root->right == nullptr)
        return root->value;
    
    root->left.find_max();
}

template <typename T>
void BST<T>::insert(const T& x) {
    //To do!
    if(is_empty()) {
        root = new BSTnode(x);
    }
    if(x > root->left) {
        root->left.insert(x);
    }else if( x < root->right) {
        root->right.insert(x);
    }
}

template <typename T>
bool BST<T>::contains(const T& x) const {
    if(is_empty())
        return false;
    
    if (root->value == x)
        return true;
    else if (x < root->value) // Recursion on the left sub-tree
        return root->left.contains(x);
    else if (x > root->value)
        return root->right.contains(x);
}
//remove element of BST
template <typename T>
void BST<T>::remove(const T& x) {
    //if the node does not have no child -> just remove from BST
    //if the node has one child -> make a pointer of parent points at child
    //if the node has two children 
    //-> 1. find the min value of the right subtree and copy to the node and delete 
    //-> will not violate BST property
    //-> 2. find the max value of the left subtree and copy to eh node and delete it
    //-> won't violate BST property
    //Do not mix 1 and 2, be consistent
    if(is_empty()) {
        return;
    }

    if(x < root->value){
        root->left.remove(x);
    }else if(x > root->value){
        root->right.remove(x);
    }else if(root->left.root && root->right.root){ //if both root->left.root and root->right.root is NOT nullptr 
        root->value = root->right.find_min();      //it means that if has two children
        root->right.remove(root->value);           //Remove the node that has min value of the right subtree
    }else{//if the node has 0 or 1 children
        BSTnode* delete_node = root;     //Save the root before deletion  
        root = (root->left.is_empty()) ? root->right.root : root->left.root; // if the root has child on right side or left side 

        //***most important to set a nullptr the deleting node's left and right to avoid actually deleting the left and right BST(Recursion)
        delete_node->left.root = delete_node->right.root = nullptr;
        delete delete_node; 
    }
}

int main() {
    
}
