#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

void insertion(int x, vector<int>& heap)
{
    heap.push_back(x);
    int child = heap.size()-1;
    int parent = 0;
    if(child%2 == 0)
    {
        parent = child/2 - 1;
    }
    else
    {
        parent = child/2;
    }
    
    while(heap[child] < heap[parent] && child>0)
    {
        // if less than its parent, move up
        //swap(heap[j], heap[j/2]);
        int temp = heap[child];
        heap[child] = heap[parent];
        heap[parent] = temp;
        child = parent;
        
        if(child%2 == 0)
        {
            parent = child/2 - 1;
        }
        else
        {
            parent = child/2;
        }
    }
}

int extractMin(vector<int>& heap)
{
    int min = heap[0];
    if(heap.size() == 1) return min;

    // Copy last element to the root 
    // then remove the last element from the list 
    heap[0] = heap.back();
    heap.pop_back();
    int n = heap.size();

    if(n==1)
    {
        return min;
    }

    int j=0;
    int l = heap[1];
    int r = heap[2];
    while(heap[j] > std::min(l, r))
    {
        if(l <= r )
        {
            //swap(heap[j], l);
            int temp = heap[j];
            heap[j] = l;
            heap[2*j+1] = temp;
            j = 2*j + 1;
        } 
        else 
        {
            //swap(heap[j], r);            
            int temp = heap[j];
            heap[j] = r;
            heap[2*j+2] = temp;
            j = 2*j + 2;    
        }
        
        if(2*j+1 > n-1)
        {
            break;
        }
        else {
            l = heap[2*j+1];
        }

        if(2*j+2 > n-1)
        {
            r = 2000000001;
        }
        else {
            r = heap[2*j+2];
        }
    }
    return min;
}

vector<int> heapSort(vector<int> arr)
{
    int min_index = 0;
    int n = arr.size();
    int min = 2000000001;
    for(int i=0; i<n; ++i)
    {
        if(arr[i] < min)
        {
            min = arr[i];
            min_index = i;
        }
    }

    vector<int> heap;
    heap.push_back(min);
    for(int i=0; i<n; ++i)
    {
        if(i==min_index) continue;
        
        insertion(arr[i], heap);
    }

    vector<int> sort;
    for(int i=0; i<n; ++i)
    {
        sort.push_back(extractMin(heap));
    }
    
    return sort;
}


int main()
{
    int n;
    cin >> n;
    vector<int> arr1(n);
    map<int, int> hashMap1;
    
    for(int i=0; i<n; ++i)
    {
        int integer;
        cin >> integer;
        
        arr1[i] = integer;
        hashMap1[integer] = i;
    }

    vector<int> arr2 = arr1;
    map<int, int> hashMap2 = hashMap1;

    const vector<int> sort = heapSort(arr1);

    //cout << "Correct order" << endl;
    int num_swap = 0;
    for(int i=0; i<n; ++i)
    {
        if(sort[i] != arr1[i])
        {
            ++num_swap;
            int index = hashMap1[sort[i]];
            hashMap1[arr1[i]] = hashMap1[arr1[index]]; 
            //swap(arr[i], arr[index]);
            int temp = arr1[i];
            arr1[i] = arr1[index];
            arr1[index] = temp; 
        }
    }

    //cout << "Reverse" << endl;
    int num_swap_reverse = 0;
    for(int i=n-1; i>=0; --i)
    {
        int reversed_index = (n-1)-i;
        if(sort[i] != arr2[reversed_index])
        {
            ++num_swap_reverse;
            int index = hashMap2[sort[i]];
            hashMap2[arr2[reversed_index]] = hashMap2[arr2[index]]; 
            //swap(arr[i], arr[index]);
            int temp = arr2[reversed_index];
            arr2[reversed_index] = arr2[index];
            arr2[index] = temp; 
        }
    }
    cout << min(num_swap_reverse, num_swap) << endl;
}
