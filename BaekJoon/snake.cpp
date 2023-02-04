#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

void print(const vector<vector<char>>& maze)
{
    for(int i=0; i<maze.size(); ++i)
    {
        for(int j=0; j<maze.size(); ++j)
        {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
}

struct Pair
{
    int y;
    int x;

    Pair(int y, int x) : y(y), x(x) {};
};

int main()
{
    int n;
    cin >> n;

    vector<vector<char>> maze(n, vector<char>(n, '*'));

    Pair curr_pos(0, 0);

    maze[curr_pos.y][curr_pos.x] = 'S';

    int n_apple;
    cin >> n_apple;

    for(int i=0; i<n_apple; ++i)
    {
        int a, b;
        cin >> a >> b;

        maze[a-1][b-1] = 'A';
    }

    int n_dir;

    cin >> n_dir;

    unordered_map<int, char> move;

    for(int i=0; i<n_dir; ++i)
    {
        int sec;
        cin >> sec;

        char dir;
        cin >> dir;

        move[sec] = dir;
    }

    bool is_running = true;

    int curr_time = 1;
    int curr_length = 0;

    Pair dir(0, 1); // (y, x)
    Pair tail_pos(0, 0);

    cout << endl;

    queue<Pair> dir_history; 

    while(true)
    {
        dir_history.push(Pair(dir.y, dir.x));

        curr_pos.y += dir.y;
        curr_pos.x += dir.x;

        cout << "At " << curr_time << endl;
        cout << "Move with " << dir.y << " " << dir.x << endl;
        cout << "Now at " << curr_pos.y << " " << curr_pos.x << endl;

        if(curr_pos.y >= n || curr_pos.x >= n || curr_pos.y < 0 || curr_pos.x < 0 ||  maze[curr_pos.y][curr_pos.x] == 'S')
        {
            cout << "Game over!" << endl;
            break;
        }

        if(maze[curr_pos.y][curr_pos.x] != 'A')
        {
            cout << "not apple" << endl;
            maze[tail_pos.y][tail_pos.x] = '*';
            Pair prev_dir = dir_history.front();
            tail_pos.y += prev_dir.y;
            tail_pos.x += prev_dir.x;

            dir_history.pop();

            cout << "Tail at " << tail_pos.y << " " << tail_pos.x << endl;
        }

        maze[curr_pos.y][curr_pos.x] = 'S';

        print(maze);

        if(move.count(curr_time))
        {
            cout << "direction change: " << move.at(curr_time) << endl;
            if(move.at(curr_time) == 'D') 
            {
                cout << "Turn right!" << endl;
                // Turn Right
                if(dir.y == 0)
                {
                    dir.y = dir.x;
                    dir.x = 0;
                }
                else
                {
                    dir.x = -dir.y;
                    dir.y = 0;
                }
            }
            else
            {
                cout << "Turn Left" << endl;
                // Turn Left
                if(dir.y == 0)
                {
                    dir.y = -dir.x;
                    dir.x = 0;
                }
                else
                {
                    dir.x = dir.y;
                    dir.y = 0;
                }
            }
        }
        ++curr_time;

        cout << endl;
    }

    cout << curr_time << endl;

    return 0;
}