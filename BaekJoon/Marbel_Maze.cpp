#include <iostream>
#include <queue>

using namespace std;

int n, m = 0;
const int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // Right, Left, Down, Up
int visit[10][10][10][10] = {0};

int init_rx, init_ry = 0;
int init_bx, init_by = 0;

struct State 
{
    int ry, rx, by, bx = 0;
    int num_move = 0;

    State() : ry(0), rx(0), by(0), bx(0), num_move(0) {};

    State(int ry, int rx, int by, int bx, int num_move) 
    : ry(ry), rx(rx), by(by), bx(bx), num_move(num_move) {};
};

ostream& operator <<(ostream& os, const State& s)
{
    return os << "Red: (" << s.ry << "," << s.rx 
                << ") and Blue: (" << s.by << "," << s.bx << ") with num move: " << s.num_move;
}

State move(State state, int dy, int dx, const vector<vector<char>>& maze)
{
    //cout << "Current State: " << state << endl;

    int curr_ry = state.ry;
    int curr_rx = state.rx;
    int curr_by = state.by;
    int curr_bx = state.bx;

    int next_ry = state.ry;
    int next_rx = state.rx;
    int next_by = state.by;
    int next_bx = state.bx;
    
    while(true)
    {
        if(maze[curr_ry + dy][curr_rx + dx] != '#' && maze[curr_ry][curr_rx] != 'O')
        {
            //cout << "Move red" << endl;
            next_ry = curr_ry + dy;
            next_rx = curr_rx + dx;
        }

        if(maze[curr_by + dy][curr_bx + dx] != '#' && maze[curr_by][curr_bx] != 'O')
        {
            //cout << "Move blue" << endl;
            next_by = curr_by + dy;
            next_bx = curr_bx + dx;
        }

        if(next_ry == next_by && next_rx == next_bx && maze[next_ry][next_rx] != 'O') 
        {
            //cout << "Red and Blue same location!" << endl;
            int dist_red = abs(next_ry-curr_ry) + abs(next_rx - curr_rx);
            int dist_blue = abs(next_by-curr_by) + abs(next_bx - curr_bx);

            if(dist_red < dist_blue)
            {
                next_by = curr_by;
                next_bx = curr_bx;
            }
            else 
            {
                next_ry = curr_ry;
                next_rx = curr_rx;
            }
        }

        //cout << "Red: (" << next_ry << "," << next_rx << ") and Blue: (" << next_by << "," << next_bx << ")" << endl;

        if( (curr_ry == next_ry && curr_rx == next_rx) && (curr_by == next_by && curr_bx == next_bx))
        {
            // If the marbels stay same location, then they cannot be moved further
            break;
        }

        curr_ry = next_ry;
        curr_rx = next_rx;

        curr_by = next_by;
        curr_bx = next_bx;

    }

    State next_state(curr_ry, curr_rx, curr_by, curr_bx, ++state.num_move);

    return next_state;
}

int bfs(const vector<vector<char>>& maze)
{
    queue<State> q;

    State init_state(init_ry, init_rx, init_by, init_bx, 0);
    State next_state;

    q.push(init_state);

    visit[init_ry][init_rx][init_by][init_bx] = true;
    
    //cout << "Init state is " << init_state << endl;

    while(!q.empty())
    {
        State state = q.front();
        q.pop();

        // cout << "Current State : " << state << endl;

        for(int i=0; i<4; ++i)
        {
            next_state = move(state, directions[i][0], directions[i][1], maze);

            if(next_state.num_move > 10)
            {
                return -1;
            }

            if(visit[next_state.ry][next_state.rx][next_state.by][next_state.bx] == false)
            {
                //std::cout << "Next state with direction (" << directions[i][0] << "," << directions[i][1] << ") : " << next_state << endl;
                // This state has never been visited before

                if(maze[next_state.ry][next_state.rx] == 'O' && maze[next_state.by][next_state.bx] == 'O')
                {
                    // With one movement, both red and blue will be in goal state, Failed
                    // Do not add this state to the queue
                    // cout << "Both in goal" << endl;
                    continue;
                }

                if(maze[next_state.ry][next_state.rx] == 'O')
                {
                    // Goal Reached
                    // cout << "Goal Reached! terminate" << endl;
                    return next_state.num_move;
                }

                visit[next_state.ry][next_state.rx][next_state.by][next_state.bx] == true;

                if(maze[next_state.by][next_state.bx] == 'O')
                {
                    // Failed, do not add this state to the queue
                    continue;
                }
                
                q.push(next_state);
            }
            //cout << endl;
        }
    }

    return -1;
}

int main()
{
    cin >> n >> m;

    vector<vector<char>> maze(n);

    for(int i=0; i<n; ++i)
    {
        string obj;
        cin >> obj;
        for(int j=0; j<m; ++j)
        {
            maze[i].push_back(obj[j]);
            if(obj[j] == 'R')
            {
                init_ry = i;
                init_rx = j;
            }
            else if (obj[j] == 'B')
            {
                init_by = i;
                init_bx = j;
            }
            
        }
    }


    //std::cout << "Red is at " << init_ry << "," << init_rx << endl;
    //std::cout << "Blue is at " << init_by << "," << init_bx << endl;

    //cout << endl;
    int path =  bfs(maze);
    cout << path << endl;

}