#include <iostream>
#include <string>

using namespace std;

int main()
{
    int n;
    cin >> n;
    string* arr = new string[n];
    for(int i=0; i<n; ++i)
    {
        int H, W, N;
        cin >> H >> W >> N;

        //cout << "H: " << H << " W: " << W << " N: " << N << endl;

        int floor = N%H;

        if(floor == 0)
        {
            floor = H;
        }

        int room = 0;
        while(N>0)
        {
            N -= H;
            room += 1;
        }
        //cout << "Floor: " << floor << " Room: " << room << endl;

        string str_floor = to_string(floor);
        string str_room = to_string(room);
        if(room < 10)
        {
            str_room = "0" + str_room;
        }

        string str_answer = str_floor + str_room;
        arr[i] = str_answer;
    }

    for(int i=0; i<n; ++i)
    {
        cout << arr[i] << endl;
    }
}