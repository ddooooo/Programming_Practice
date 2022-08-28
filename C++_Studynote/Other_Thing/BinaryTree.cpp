#include <iostream>
#include <queue>
using namespace std;

//length of path -> the number of edges on the path
//Depth of node -> look downward from root to the node, the number of edges from root to node(downward)
//Height of node -> look upward from leaf(the bottom most) that gives the longest path to node, the number of edges from leaf to node(upward)
//Ancestor(include itself) and proper Ancestor(it does not include itself)
//Decendent(include itself) and proper Decendent(it does not include itself)
//Binary Tree -> each node can be connected with at most two nodes(each node must have at most two children,decendent)
//Good binary tree -> the height of right subtree and left subtree is same -> it is balanced, O(logN)
//the worst tree -> O(n)
//leave node, external nodes -> the node with child node
//non leave node, internal nodes -> the node without child node
//Page 22




//Binary tree can be class Template
template<class T> 
class BTnode {
    private:
        T data; //the information of node
        BTnode* left;
        BTnode* right;
    
    public:
        BTnode(const T& x, BTnode* L = nullptr, BTnode* R = nullptr){
            data = x;
            left = L;
            right = R;
        }
        ~BTnode() {
            delete left; // if have p as the pointer to the root, *delete p* -> call destructor of BTnode -> *delete left* -> call destructor of left sub BTnode
            delete right; // if all left subnodes have been deleted -> delete right -> call destructor of right sub BTnode -> it implies it recursively delete the nodes
            cout << "delete the node with data = " << data << endl;
        }
        T get_data() {
            return data;
        }
        BTnode* get_left() {
            return left;
        }
        BTnode* get_right() {
            return right;
        }
};

template <typename T>
void print(BTnode<T>* root) { 
    cout << root->get_data() << endl; 
}

//Inorder traversal -> scan through all node in Tree -> Left,Current,Right -> the current node should be in the middle
//       A
//     B   C
//    D E   
// D -> B -> E -> A -> C // go back to parent node when all left, current, right nodes of child node have been scanned
//Inorder -> recursion function
template <typename T>
void btree_inorder(BTnode<T>* root, void (*action) (BTnode<T>*)) { //function pointer it takes the funtion *action* that has paramter *BTnode<T>* r* -> pass each node in the function *action*
    if(root) { // base condition, if the node is nullptr -> the function is stopped
        btree_inorder(root->get_left(), action); // call the function recursively and pass the leftnode of root to the function 
        action(root); //print out root->data
        btree_inorder(root->get_right(), action); // // call the function recursively and pass the rightnode of root to the function
    }
}

//Preorder Traversal -> Current, Left, Right
//       A
//      B  C
//     D E  
// A -> B -> D -> E -> C
//Preorder Traversal
template <typename T>
void btree_preorder(BTnode<T>* root, void (*action) (BTnode<T>* r)) { //function pointer it takes the funtion *action* that has paramter *BTnode<T>* r* -> pass each node in the function *action*
    if(root) { // base condition, if the node is nullptr -> the function is stopped
        action(root); //print out root->data
        btree_preorder(root->get_left(), action); // call the function recursively and pass the leftnode of root to the function 
        btree_preorder(root->get_right(), action); // // call the function recursively and pass the rightnode of root to the function
    }
}

//Postorder Traversal -> Left, Right, Current
//       A
//     B   C
//    D E 
// (Left, Right,)D -> E -> B -> C -> A
//Postorder Traversal
template <typename T>
void btree_postorder(BTnode<T>* root, void (*action) (BTnode<T>* r)) { //function pointer it takes the funtion *action* that has paramter *BTnode<T>* r* -> pass each node in the function *action*
    if(root) { // base condition, if the node is nullptr -> the function is stopped
        btree_postorder(root->get_left(), action); // call the function recursively and pass the leftnode of root to the function 
        btree_postorder(root->get_right(), action); // // call the function recursively and pass the rightnode of root to the function
        action(root); //print out root->data
    }
}

//Level order traversal using Queue -> need to implement
//       A
//     B   C
//    D E 
// A -> B -> C -> D -> E
//More like BFS Algorithm
template <typename T>
void btree_levelorder(BTnode<T>* root, void (*action) (BTnode<T>* r)) {
    if(root) {
        queue<BTnode<T> *> q; // empty queue
        q.push(root);

        while( q.empty() == false ) {
            
            BTnode<T>* t = q.front();
            //cout << t->get_data() << endl;
            action(t);
            q.pop();
            if(t->get_left()) {
                q.push(t->get_left());
            }
            if(t->get_right()) {
                q.push(t->get_right());
            }

        }
    }
}

int main() {
    BTnode<int>* node1 = new BTnode<int>(10);
    BTnode<int>* node2 = new BTnode<int>(20);
    BTnode<int>* node3 = new BTnode<int>(30, node1, node2);

    BTnode<int>* node4 = new BTnode<int>(40);
    BTnode<int>* node5 = new BTnode<int>(50);
    BTnode<int>* node6 = new BTnode<int>(60, node4, node5);

    BTnode<int>* node7 = new BTnode<int>(70, node3, node6);

    cout << "Level order" << endl;
    btree_levelorder(node7, print);

}
