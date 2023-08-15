#include<iostream>
#include<vector>
#include<queue>

using namespace std;

typedef vector<vector<int>> B;

int findSameColors(int x, int y, int color, B& grid)
{
    int num_cars = 1;
	cout << "Find color " << color << " at (" << y << ", " << x << ") " << endl; 
	int h = grid.size();
	int w = grid[0].size();
	
	if( (x<0 & y<0) || (x>w & y>h) || grid[y][x] == 0)
		return 0;

	grid[y][x] = 0;

	if(y+1<h)
	{	
		if(color==grid[y+1][x])
			num_cars += findSameColors(x, y+1, color, grid);
	}
	
	if(y-1>=0)
	{
		if(color == grid[y-1][x])
			num_cars += findSameColors(x, y-1, color, grid);
	}
	
	if(x+1<w)
	{
		if(color == grid[y][x+1])
			num_cars += findSameColors(x+1, y, color, grid);
	}
	
	if(x-1>=0)
	{
		if(color == grid[y][x-1])
			num_cars += findSameColors(x-1, y, color, grid);
	}
    // cout << num_cars << endl;
	return num_cars;
}

int getArea(B& state, int color)
{
	// cout << "Get Area " << endl;
    int min_x = 20;
    int min_y = 20;

	int max_x = -1;
	int max_y = -1;

	for(int y=0; y<state.size(); ++y)
	{
		for(int x=0; x<state.size(); ++x)
		{
			if(state[y][x]==0)
			{
				if(x < min_x) min_x = x;
                if(y < min_y) min_y = y;
                if(x > max_x) max_x = x;
                if(y > max_y) max_y = y;
			}
		}
	}
    cout << "Area : " << max_x << " " << max_y << " / " << min_x << " " << min_y << endl;
	int area_w = (max_x - min_x) + 1;
	int area_h = (max_y - min_y) + 1;
	cout << "--> Area : " << area_h << " " << area_w << endl;
    if(area_w < 0)
    {
        area_w = 0;
    }

    if(area_h < 0)
    {
        area_h = 0;
    }
	return area_h*area_w;
}

void updateBoard(B& game, B& left, int color)
{
	int n = game.size();
	int loc_h = 2*n-1;
	cout << "Update board! " << loc_h << endl;


	// Update game
	for(int y=n-1; y>=0; --y)
	{
		for(int x=0; x<n; ++x)
		{
			if(game[y][x] == 0)
			{
				if(left[loc_h][x] != 0)
				{
                    cout << "Update board at " << y << ", " << x << " with  " << loc_h << " " << left[loc_h][x] <<   endl;
					game[y][x] = left[loc_h][x];
					left[loc_h][x] = 0;
				}
			}
		}
		--loc_h;
	}
    
	for(int y=0; y<2*n; ++y)
	{
		for(int x=0; x<n; ++x)
		{
            cout << left[y][x] << " ";
        }
        cout << endl;
    }

	// Update left
	for(int y=2*n-1; y>0; --y)
	{
		for(int x=0; x<n; ++x)
		{
			if(left[y][x] == 0)
			{
                int temp = y-1;
                while(left[temp][x] == 0 & temp>=0)
                {
                    cout << "cannot get from : (" << temp << ", " << x << ") " << left[temp][x] << endl;
                    --temp;
                }
                if(temp < 0)
                {
                    // cout << "  > continue " << endl;
                    continue;
                }
                cout << "get from : (" << temp << ", " << x << ") " << left[temp][x] << endl;
            
				left[y][x] = left[temp][x];
				left[temp][x] = 0;
			}
		}
	}
}

int play(B game, B left, int turn)
{
	if(turn >= 3)
	{
		cout << "Exceed number of turns stop!" << endl;
		return 0;
	}

	if(game.empty())
	{
		cout << "Stop play" << endl;
		return 0;
	}

	int max_point = 0;
	for(int y=0; y<game.size(); ++y)
	{
		for(int x=0; x<game.size(); ++x)
		{
			cout << "select at (" << y << ", " << x << ") " << endl; 
            for(int y=0; y<game.size(); ++y)
            {
                for(int x=0; x<game.size(); ++x)
                {
                    cout << game[y][x] << " ";
                }
                cout << endl;
            }

            B temp = game;
			int step = turn;

			if(game[y][x] == 0) continue;

			int color = game[y][x];

			int num_cars = findSameColors(x, y, color, game);
            
            if(num_cars == 1)
                num_cars = 0;

			int area = getArea(game, color);
			
			int curr_point = 0;
			if(area > 1)
			{	
                B next = game;
                B next_left = left;
				updateBoard(next, next_left, color);
                int next_point = play(next, next_left, ++step);
				curr_point += num_cars + area + next_point;
			}
            else
            {
                game = temp;
            }

			if(curr_point>max_point)
			{
				max_point=curr_point;
			}
		}
	}

	return max_point;
}

int main(int argc, char** argv)
{

	int n;
	cin >> n;
	B b;
	for(int i=0; i<3*n; ++i)
	{
		vector<int> t;
		for(int j=0; j<n; ++j)
		{
			int v;
			cin >> v;
			t.push_back(v);
		}
		b.push_back(t);
	}

	B left;
	B game;

	for(int y=2*n; y<3*n; ++y)
	{
		vector<int> line;
		for(int x=0; x<n; ++x)
		{
			line.push_back(b[y][x]);
		}
		game.push_back(line);
	}

	for(int y=0; y<2*n; ++y)
	{
		vector<int> line;
		for(int x=0; x<n; ++x)
		{
			line.push_back(b[y][x]);
		}
		left.push_back(line);
	}

	cout << play(game, left, 0) << endl;
}