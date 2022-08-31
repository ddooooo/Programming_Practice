#include <iostream>
#include <vector>
#include <map>

using namespace std;

// Use dfs algorithm (with recursion) to find all connected graph and get number of roads required for each connected graph
// calculate the cost of building library and roads

void DFS_visit(long &n_roads, int node, const vector<vector<int>> &g, vector<bool> &visit)
{
    //cout << "Visit: " << node << endl;
    for(int i=0; i<g[node].size(); ++i)
    {
        int nbor = g[node][i];
        if(visit[nbor] == false)
        {
            //cout << "Visit neighbor: " << nbor << endl;
            n_roads += 1;
            visit[nbor] = true;
            DFS_visit(n_roads, nbor, g, visit); 
        }
    }
}

long DFS(const vector<vector<int>> &g, const int n, const long c_lib, const long c_road)
{
    vector<bool> visit(n, false);
    long n_roads = 0;
    long long total_cost = 0;
    
    for(int i=0; i<n; ++i)
    {
        if(visit[i] == false)
        {
            n_roads = 0;
            visit[i] = true;
            //cout << "Looping visit: " << i << " " << n_roads << endl;
            DFS_visit(n_roads, i, g, visit);
            
            //cout << "n_roads " << n_roads << endl;
            //cout << "total: " << (n_roads * c_road) + c_lib << endl;
            long long road_costs = (n_roads * c_road);
            total_cost += road_costs + c_lib;
        }
    }

    return total_cost;
}

int main()
{
    int nq;
    cin >> nq;
    
    for(int q_iter=0; q_iter<nq; ++q_iter)
    {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> g(n);
        
        long c_lib, c_road;
        cin >> c_lib >> c_road;
        
        for(int i=0; i<m; ++i)
        {
            int s, d;
            cin >> s >> d;
            
            g[s-1].push_back(d-1);
            g[d-1].push_back(s-1);
        }
        
        //cout << DFS(g, n) << endl;
        long long cost = DFS(g,n, c_lib, c_road);
        long long c_libs = n * c_lib;
        //cout << "cost: " << cost << " lib: " << c_libs << endl;
        // cout << "Cost of roads " << c_roads << " and Cost of lib " << c_libs << endl;
        long total_cost = ( c_libs <= cost ) ? c_libs : cost;
        // cout << "Total cost " << total_cost << endl;
        cout << total_cost << endl;
    }
}
