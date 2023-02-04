#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct State
{
    int n_move;
    vector<vector<int>> board;
    
    State() {n_move = 0; board = {};};
    State(vector<vector<int>> board, int n_move) : board(board), n_move(n_move) {};
};

void printBoard(const vector<vector<int>>& board)
{
    for(int i=0;i<board.size();++i)
    {
        for(int j=0; j<board.size(); ++j)
        {
            cout << board.at(i).at(j);
        }
        cout << endl;
    }

    cout << endl;
}

void printTrack(const vector<vector<bool>>& track)
{
        //cout << board.size() << endl;
    for(int i=0;i<track.size();++i)
    {
        for(int j=0; j<track.size(); ++j)
        {
            cout << track.at(i).at(j);
        }
        cout << endl;
    }

    cout << endl;
}

void flipDiagonal(State& state)
{
    vector<vector<int>> original_board = state.board;

    int n = original_board.size();

    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            state.board[i][j] = original_board[j][i];
        }
    }
}

void flipHorizontal(State& state)
{
    int n = state.board.size();

    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n/2; ++j)
        {
            int temp = state.board[i][j];
            state.board[i][j] = state.board[i][n-j-1];
            state.board[i][n-j-1] = temp;
        }
    }
}

void flipBack(State& state, int dir)
{
    switch(dir)
    {
        case 0: 
            // left
            break;
        case 1:
            // up
            flipDiagonal(state);
            break;
        case 2:
            // right
            flipHorizontal(state);
            break;
        case 3:
            // down
            flipHorizontal(state);
            flipDiagonal(state);
            break;
        default:
            break;
    }
}

void move(vector<vector<int>>& board, vector<vector<bool>>& track)
{
    vector<vector<int>> original = board;

    int n = board.size();

    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n-1; ++j)
        {
            if(board[i][j] == 0)
            {
                board[i][j] = board[i][j+1];
                board[i][j+1] = 0;
                track[i][j] = track[i][j+1];
            }
            else if( (board[i][j] == board[i][j+1]) && (track[i][j] == 0 && track[i][j+1] == 0) )
            {
                board[i][j] *= 2;
                board[i][j+1] = 0;
                track[i][j] = 1;
            }
        }
    }

    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            if(board[i][j] != original[i][j])
            {
                return move(board, track);
            }
        }
    }
}

State process(const State& state, int dir)
{
    vector<vector<int>> next_board = state.board;

    State next_state(next_board, state.n_move + 1);

    switch(dir)
    {
        case 0: 
            // left
            break;
        case 1:
            // up
            flipDiagonal(next_state);
            break;
        case 2:
            // right
            flipHorizontal(next_state);
            break;
        case 3:
            // down
            flipDiagonal(next_state);
            flipHorizontal(next_state);
            break;
        default:
            break;
    }


    vector<vector<bool>> track(next_board.size(), vector<bool>(next_board.size(), 0));

    move(next_state.board, track);

    flipBack(next_state, dir);
    
    return next_state;
}

int bfs(vector<vector<int>> board)
{
    queue<State> q;

    int size = board.size();
    State init_state(board, 0);
    q.push(init_state);

    State next_state;

    int maximum = 0;

    while(!q.empty())
    {
        State state = q.front();
        q.pop();

        for(int i=0;i<4;++i)
        {
            next_state = process(state, i);

            //cout << "Process to next state with move: " << next_state.n_move << endl;
            vector<vector<int>> board = next_state.board;
            for(int i=0; i<size; ++i)
            {
                for(int j=0; j<size; ++j)
                {
                    if(board.at(i).at(j) > maximum)
                    {
                        maximum = board[i][j];
                        cout << "Maximum with " << maximum << " " << next_state.n_move << endl;
                        printBoard(next_state.board);
                    }
                }
            }

            if(next_state.n_move >= 5) continue;

            q.push(next_state);
        }
    }

    return maximum;
}

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> board(n);

    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            int num;
            cin >> num;
            board[i].push_back(num);
        }
    }

    int max_point = bfs(board);
    cout << max_point << endl;

    return 0;
}