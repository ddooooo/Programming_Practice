#include <iostream>
#include <vector>

using namespace std;

int max_key = 1000000001;

struct Node
{
    int node;
    int fish;
    int dist;
    Node(int n, int f, int d) : node(n), fish(f), dist(d) {}
};

inline const Node& min(const Node& a, const Node& b)
{
    return (a.dist < b.dist) ?  a :  b;
} 

inline bool operator<(const Node& a, const Node& b)
{
    return (a.dist < b.dist) ? true : false;
}

inline bool operator<=(const Node& a, const Node& b)
{
    return (a.dist <= b.dist) ? true : false;
}

inline ostream& operator<<(ostream& os, const Node& n)
{
    return os << n.node << " " << n.fish << " " << n.dist << " ";
}

void insertion(Node x, vector<Node>& heap)
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
        Node temp = heap[child];
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

Node extractMin(vector<Node>& heap)
{
    Node min_node = heap[0];
    //cout << "Extract Min: " << min_node << endl;
    
    if(heap.size() == 1)
    {
        heap.pop_back();
        return min_node;
    }

    // Copy last element to the root 
    // then remove the last element from the list 
    heap[0] = heap.back();
    heap.pop_back();
    int n = heap.size();

    if(n==1)
    {
        return min_node;
    }

    int j=0;
    Node l = heap[1];
    Node r = heap[2];
    while(min(l, r) < heap[j])
    {
        if(l <= r)
        {
            //swap(heap[j], l);
            Node temp = heap[j];
            heap[j] = l;
            heap[2*j+1] = temp;
            j = 2*j + 1;
        } 
        else 
        {
            //swap(heap[j], r);            
            Node temp = heap[j];
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
            r.dist = max_key;
        }
        else {
            r = heap[2*j+2];
        }
    }

    return min_node;
}

vector<vector<int>> shopping(int n, int k, Node start, const vector<vector<Node>>& adj, const vector<vector<int>>& weights)
{
    vector<Node> Q;
    vector<vector<int>> key(n, vector<int>(1<<k));
    
    //cout << "Shopping Start!" << endl;

    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<(1<<k); ++j)
        {
            key[i][j] = max_key;
        }
    }


    insertion(start, Q);
    key[0][start.fish] = 0;

    while(!Q.empty())
    {
        Node u = extractMin(Q);

        //cout << "After extract" << endl;
        // for(int i=0; i<Q.size(); ++i)
        // {
        //     cout << Q[i] << endl;
        // }

        if(u.dist != key[u.node][u.fish]) continue;

        for(int i=0; i<adj[u.node].size(); ++i)
        {
            Node v = adj[u.node][i];
            int new_fish = u.fish | v.fish;
            int sv = u.dist + weights[u.node][v.node];

            if(sv < key[v.node][new_fish])
            {
                v.dist = sv;
                v.fish = new_fish;
                //cout << "Update the node: " << v << endl;
                key[v.node][new_fish] = sv;
                insertion(v, Q);
            }
        }
        //cout << endl;
    }

    return key;
}

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> shop(n);

    for(int i=0; i<n; ++i)
    {
        int n_fish;
        cin >> n_fish;
        //shop[i] = vector<int>(n_fish);
        for(int j=0; j<n_fish; ++j)
        {
            int type;
            cin >> type;
            shop[i] |= 1<<(type-1);
        }
    }

    vector<vector<Node>> adj(n);
    vector<vector<int>> weights(n, vector<int>(n));

    for(int i=0; i<m; ++i)
    {
        int a, b;
        cin >> a >> b;
        
        Node u(a-1, shop[a-1], 0);
        Node v(b-1, shop[b-1], 0); 

        adj[a-1].push_back(v);
        adj[b-1].push_back(u);

        int w;
        cin >> w;
        weights[a-1][b-1] = w;
        weights[b-1][a-1] = w;
    }   

    Node start(0, shop[0], 0);

    vector<vector<int>> key = shopping(n, k, start, adj, weights);

    int result = max_key;

    for(int i=0; i<(1<<k); ++i)
    {
        for(int j=0; j<(1<<k); ++j)
        {
            if(i|j == 1<<(k-1))
            {
                int time = std::min(key[n-1][i], key[n-1][j]);
                if(time < result)
                {
                    result = time;
                }
            }
        }
    }

    cout << result << endl;
}