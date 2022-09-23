#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <array>

using namespace std;

typedef pair<pair<int, int>, int> EDGE;

ostream& operator<<(ostream& os, EDGE e)
{
    return os << "From " << e.first.first << " to " << e.first.second << " with " << e.second << endl;
}

void swap(vector<EDGE>& graph, int i, int j)
{
    //cout << "Swapp with " << i << " and " << j << endl;
    if(i == j)
    {
        return;
    }

    EDGE temp = graph[i];
    graph[i] = graph[j];
    graph[j] = temp;

    //cout << "i: " << graph[i] << endl;
    //cout << "j: " << graph[j] << endl;
}

int partition(vector<EDGE>& graph, int p, int r)
{
    int last = graph[r].second;

    int i = p-1;
    //cout << "last weight: " << last << endl;

    for(int j=p; j<r; ++j)
    {
        //cout << j << ": " << graph[j].second << endl;
        if(graph[j].second <= last)
        {
            ++i;
            swap(graph, i, j);
        }
    }

    //cout << "Swap before return" << endl;
    swap(graph, i+1, r);

    return i+1;
}

void quickSort(vector<EDGE>& graph, int p, int r)
{
    // p -> the index of first element, r -> the index of last element
    
    // Base case
    if(p >= r) return;

    //cout << "p: " << p << " r: " << r << endl;
    
    int q = partition(graph, p, r);

    quickSort(graph, p, q-1);
    quickSort(graph, q+1, r);
}


pair<int, int> findSet(const vector<int>& parent, int x)
{
    int start = x;
    int height = 0;
    // Loop until it finds the root node
    while(x != parent[x])
    {
        height++;
        x = parent[x];
    }
    cout << "Found the root from " << start << ": " << x << " with height: " << height << endl; 
    return make_pair(x, height);
}

void Union(vector<int>& parent, const pair<int, int>& a, const pair<int, int>& b)
{
    if(a.second <= b.second)
    {
        cout << "a to b: ";
        cout << a.first << " to " << b.first << endl;  
        parent[a.first] = b.first;
    }
    else
    {
        cout << "b to a: "; 
        cout << b.first << " to " << a.first << endl;  
        parent[b.first] = a.first;
    }
}

int kruskal(const vector<EDGE>& graph, int n_nodes)
{
    // Sort the the weight in increasing order
    // 1. Select the lowest edge and check whether it creates a cycle
    // 2. if not, remove from the list and push it to the tree
    // 3. if yes, ignore
    // 4. Go back to 1

    int result = 0;

    vector<int> parent(n_nodes);

    // Make set
    cout << "Make set" << endl;
    for(int i=1; i<n_nodes+1; ++i)
    {
        parent[i] = i;
        cout << parent[i];
    }
    cout << endl;
    // Loop over edges in increasing order of their weights
    for(int i=0; i<graph.size(); ++i)
    {
        auto e = graph[i];
        int u = e.first.first;
        int v = e.first.second;
        cout << "u: " << u << " v: " << v << endl;
        cout << "parent u: " << parent[u] << " parent u: " << parent[v] << endl;
        auto a = findSet(parent, u);
        auto b = findSet(parent, v);

        if(a.first != b.first)
        {
            result += e.second;
            Union(parent, a, b);
            cout << "Result: " << result << endl;
        }
    }

    return result;
}

int main()
{
    int n_nodes, n_edges;

    cin >> n_nodes >> n_edges;

    vector<EDGE> graph(n_edges);
    vector<vector<int>> weights(n_nodes, vector<int>(n_nodes, 100001));

    for(int i=0; i<n_edges; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        //cout << "From " << u << " to " << v << " with " << w << endl;

        auto uv = make_pair(u, v);

        EDGE e = make_pair(uv, w);

        graph[i] = e;
    }

    cout << "Graph" << endl;

    for(auto& it : graph)
    {
        cout << it << endl;
    }

    cout << "After sorted" << endl;
    int r = graph.size()-1;
    quickSort(graph, 0, r);

    for(auto& it : graph)
    {
        cout << it << endl;
    }

    cout << kruskal(graph, n_nodes);

}