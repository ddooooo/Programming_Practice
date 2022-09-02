#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void updateQ(vector<pair<int,int>>& Q, int node, int weight)
{
    for(int i=0; i<Q.size(); ++i)
    {
        if(Q[i].first == node)
        {
            Q[i].second = weight;
            cout << "Update Q[v] " << node << " " << Q[i].second << endl;
            return;
        }
    }
}

int extractMin(vector<pair<int,int>>& Q)
{
    int index = 0;
    int min_key = 10001;
    //pair<int, int> min_node;
    int min_node;
    for(int i=0; i<Q.size(); ++i)
    {
        if(Q[i].second < min_key)
        {
            min_node = Q[i].first;
            min_key = Q[i].second;
            index = i;
        }
    }
    cout << "Extract Min " << min_node << endl;
    
    Q.erase(Q.begin()+index);
    

    cout << "After extract" << endl;
    for(int i=0; i<Q.size(); ++i)
    {
        cout << Q[i].first << " " << Q[i].second << " ";
    }
    cout << endl;

    return min_node;
}


int dijkstra(int n, int start, int last, vector<bool>& f, vector<queue<int>>& s,
                                const vector<vector<int>>& w, const vector<vector<int>>& adj)
{
    cout << "Find shortest path" << endl;

    vector<int> key(n, 10001);
    vector<int> parent(n, -1);
    vector<bool> visit(n, false);
    vector<int> child(n);

    vector<pair<int, int>> Q;

    key[start] = 0;
    visit[start] = true;

    for(int i=0; i<n; ++i)
    {
        pair<int, int> node = make_pair(i, key[i]);
        Q.push_back(node);
    }

    while(!Q.empty())
    {
        int u = extractMin(Q);
        if(parent[u] != -1)
        {
            cout << "Move to " << u << " " << key[u] << endl;
        }
        cout << "Relaxation of all the neighbor nodes" << endl;
        for(int i=0; i<adj[u].size(); ++i)
        {
            int v = adj[u][i];
            int s_to_v = w[u][v] + key[u];
            for(int j=0; j<s[v].size(); ++j)
            {
                
            }
            if(!visit[v] && s_to_v < key[v])
            {
                cout << "V: " << v << endl;
                cout << "Path from s to v: " << s_to_v << endl;
                visit[v] = true;
                key[v] = s_to_v;
                parent[v] = u;
                updateQ(Q, v, s_to_v);
            }
        }
    }

    int node = last;
    while(node >= 0)
    {
        int type = s[node].front();
        s[node].pop();
        f[type] = true;
        cout << "node: " << node << " ";
        node = parent[node];
    }
    cout << endl;

    cout << key[last] << endl;
    int path = key[last];
    return path;
}

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<queue<int>> shop(n);
    vector<bool> fish(k, false);
    
    for(int i=0; i<n; ++i)
    {
        int n_fish;
        cin >> n_fish;
        //shop[i] = vector<int>(n_fish);
        for(int j=0; j<n_fish; ++j)
        {
            int type;
            cin >> type;
            shop[i].push((type-1));
        }
    }
    

    vector<vector<int>> adj(n);
    vector<vector<int>> weights(n, vector<int>(n));

    for(int i=0; i<m; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj[u-1].push_back(v-1);
        adj[v-1].push_back(u-1);

        int w;
        cin >> w;
        weights[u-1][v-1] = w;
        weights[v-1][u-1] = w;
    }

    dijkstra(n, 0, n-1, fish, shop, weights, adj);

}