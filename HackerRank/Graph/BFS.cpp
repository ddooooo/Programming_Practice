#include <iostream>
#include <queue>
using namespace std;

vector<int> bfs(int n_node, int s, vector<vector<int>> g)
{
    vector<int> dist(n_node, -1);
    vector<bool> visit(n_node, false);
    queue<int> q;
    
    //cout << "Starting node: " << s << endl;
    
    q.push(s);
    visit[s] = true;
    dist[s] = 0;
    while(!q.empty())
    {
        int node = q.front();
        q.pop();
        //cout << "Visit node: " << node << endl;
        
        for(int i=0; i<g[node].size(); ++i)
        {
            int nbor = g[node][i];
            //cout << "It's neighbor: " << nbor << endl;
            if(visit[nbor] == false)
            {
                //cout << "First time visited!" << endl;
                q.push(nbor);
                visit[nbor] = true;
                dist[nbor] = 1 + dist[node];
            }
        }
    }
    
    //cout << "Queue empty, done!" << endl;
    
    return dist;
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
        for(int i=0; i<m; ++i)
        {
            int a, b;
            cin >> a >> b;
            g[a-1].push_back(b-1);
            g[b-1].push_back((a-1));
        }
        
        int s;
        cin >> s;
        
        vector<int> dist = bfs(n, --s, g);    
        
        //cout << "Distance : ";
        for(int d_iter=0; d_iter<dist.size(); ++d_iter)
        {
            int d = dist[d_iter];
            //cout << "Distance: " << d << " ";
            if(d == 0) continue;
            
            if(d==-1)
            {
                cout << dist[d_iter] << " ";
            }
            else {
                cout << dist[d_iter]*6 << " ";
            }
            
        }
        cout << endl;
    }
}
