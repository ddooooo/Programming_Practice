#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache : public Cache
{
    public:
        LRUCache(int capacity)
        {
            cp = capacity;
            head = nullptr;
            tail = nullptr;
        }
        
        void set(int k, int v)
        {
            cout << "Set: " << k << " " << v << endl;
            if(mp[k] == nullptr)
            {
                cout << "Size of map: " << mp.size() << endl;
                mp[k] = new Node(nullptr, head, k, v);
                
                if(head) 
                {
                    cout << "Current head: " << head->key << " " << head->value << endl;
                    head->prev = mp[k];
                }
                head = mp[k];
                
                Node* temp = head->next;
                while(temp)
                {
                    tail = temp;
                    temp = temp->next;
                }

                if(mp.size() > cp)
                {
                    // Delete tail node
                    mp.erase(tail->key);
                    tail = tail->prev;
                    delete tail->next;
                    tail->next = nullptr;
                }
            }
            else 
            {
                // Update value
                mp[k]->value = v;
                
                if(mp[k] == head) return; // if the node is head

                // Move the node to the head
                mp[k]->prev->next = mp[k]->next;

                if(mp[k] == tail)
                {
                    // if the node is tail
                    tail = tail->prev;
                }
                else
                {
                    mp[k]->next->prev = mp[k]->prev;
                }

                mp[k]->prev = nullptr;
                mp[k]->next = head;
                head->prev = mp[k];
                head = mp[k];
            }
        }

        int get(int k)
        {
            if(mp[k] != nullptr)
            {
                return mp[k]->value;
            }
            return -1;
        }
};

int main() {
    int n, capacity,i;
    cin >> n >> capacity;
    LRUCache l(capacity);
    for(i=0;i<n;i++) 
    {
        string command;
        cin >> command;
        if(command == "get") {
            int key;
            cin >> key;
            cout << l.get(key) << endl;
        } 
        else if(command == "set")
        {
            int key, value;
            cin >> key >> value;
            l.set(key,value);
        }
    }
    return 0;
}
