#include <string>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

typedef pair<int, int> POS;

POS findNext(POS pos, vector<vector<int>>& grid, int dir, int d)
{
    int curr_pos = grid[pos.first][pos.second];
    int h = grid.size();
    int w = grid[0].size();
    cout << "Find next - Current value : " << curr_pos <<  " dirction:  " << dir  << " need to safisfy " << d<< endl;
    POS next(-1, -1);
    if(dir==0 & pos.first-1>=0)
    {
        // Go up
        int next_pos = grid[pos.first-1][pos.second];
        if(next_pos-curr_pos == d)
        {
            next = POS(pos.first-1, pos.second);
            cout << "  -UP: To " << next_pos << " with (" << next.first << ", " << next.second << ")" << endl;
        }
    }
    else if(dir==1 & pos.first+1<h)
    {
        // Go down
        int next_pos = grid[pos.first+1][pos.second];
        if(next_pos-curr_pos == d)
        {
            next = POS(pos.first+1, pos.second);
            cout << "  -DOWN: To " << next_pos << " with (" << next.first << ", " << next.second << ")" << endl;
        }

    }
    else if(dir==2 & pos.second-1>=0)
    {
        // Go left
        int next_pos = grid[pos.first][pos.second-1];
        if(next_pos-curr_pos == d)
        {
            next = POS(pos.first, pos.second-1);
            cout << "  -LEFT: To " << next_pos << " with (" << next.first << ", " << next.second << ")" << endl;
        }
    }
    else if(dir==3 & pos.second+1<w)
    {
        //Go right
        int next_pos = grid[pos.first][pos.second+1];
        // cout << "Next post : " << next_pos << endl;
        if(next_pos-curr_pos == d)
        {
            next = POS(pos.first, pos.second+1);
            cout << "  -RIGHT: To " << next_pos << " with (" << next.first << ", " << next.second << ")" << endl;
        }
    }
    
    return next;
}

int findPath(queue<POS> starts, vector<vector<int>>& grid, vector<int>& d, int k, int num_steps)
{
    if(starts.empty())
    {
        cout << "Stuck" << endl;
        return 0;
    }
        
    queue<POS> next;
    while(!starts.empty())
    {
        POS start = starts.front();
        starts.pop();
        for(int i=0; i<4; ++i)
        {
            int incline = d[ (num_steps)%d.size() ];
            POS pos = findNext(start, grid, i, incline);
            if(pos.first<0 & pos.second<0) continue;
            next.push(pos);
        }
    }

    if(num_steps == d.size()*k-1)
    {
        cout << "Reach maximum! at " << num_steps << " with " << next.size() << endl;
        return next.size();
    }

    return findPath(next, grid, d, k, ++num_steps);
}

int solution(vector<vector<int>> grid, vector<int> d, int k) 
{
    int answer = 0;
    
   for(int h=0; h<grid.size(); ++h)
    {
       for(int w=0; w<grid[0].size(); ++w)
       {
            queue<POS> start;
            start.push(POS(h, w));
            int result = findPath(start, grid, d, k, 0);
            answer += result;
            // cout << "At (" << h << "," << w << ") :  " << result << endl;
       }
   }
    int dividend = (1e9+7);
    return answer % dividend;
}

int main()
{
    vector<vector<int>> grid = {{3, 4, 6, 5, 3}, {3, 5, 5, 3, 6}, {5, 6, 4, 3, 6}, {7, 4, 3, 5, 0} };
    vector<int> d = {1, -2, -1, 0, 3};
    int k = 1;
    // vector<vector<int>> grid = {{0, 0, 0}, {1, 0, 0}, {0, 0, 0}, {0, 0, 1}, {1, 0, 0}};
    // vector<int> d = {0, 0, 1, -1, 0, 0, 1, -1};
    // int k = 1;

    cout << solution(grid, d, k) << endl; 
}