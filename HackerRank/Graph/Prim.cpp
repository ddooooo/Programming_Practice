#include <iostream>
#include <vector>

using namespace std;

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
    
    return min_node;
}

int prim(int start, int n, vector<vector<int>>& shop, vector<bool>& fish, 
                        vector<vector<int>>& w, vector<vector<int>>& adj)
{
    vector<int> parent(n, -1);
    vector<int> key(n, 10001);
    vector<pair<int, int>> Q(n);
    
    key[0] = 0;
    cout << shop[0][0] << endl;
    fish[ shop[0][0] ] = true;

    for(int i=0; i<Q.size(); ++i)
    {
        Q[i] = make_pair(i, key[i]);
    }

    int big_cat = 0;
    while(Q.empty() == false)
    {
        cout << "Explore" << endl;
        int node = extractMin(Q);
        
        if(parent[node] != -1)
        {
            for(int i=0; i<shop[node].size(); ++i)
            {
                int type = shop[node][i];
                if(fish[type] == false)
                {
                    big_cat += key[node];
                    fish[type] = true;
                    break;
                }
            }
        }
        
        for(int i=0; i<adj[node].size(); ++i)
        {
            int nbor = adj[node][i];
            int new_w = w[node][nbor];
            if( new_w < key[nbor])
            {
                cout << "Update node!" << endl;
                cout << node << " to " << nbor << " with " << new_w << endl;
                key[nbor] = w[node][nbor];
                Q[nbor].second = key[nbor];
                parent[nbor] = node;
            }
        }
    }
}

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> shop(n);
    vector<bool> fish(k, false);
    
    for(int i=0; i<n; ++i)
    {
        int n_fish;
        cin >> n_fish;
        for(int j=0; j<n_fish; ++j)
        {
            int type;
            cin >> type;
            shop[i].push_back(type-1);
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
        cout << "w: " << w << endl;
        weights[u-1][v-1] = w;
        weights[v-1][u-1] = w;
    }
}