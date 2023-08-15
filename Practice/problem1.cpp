#include <string>
#include <vector>
#include <iostream>
#include <algorithm> // std::min_element
#include <queue>
using namespace std;

int getMin(vector<int>& q)
{
    int min = INT_MAX;
    int index = 0;
    for(int i=0; i<q.size(); ++i)
    {
        if(q[i]<min)
        {
            min = q[i];
            index = i;
        }
    }

    q.erase(q.begin()+index);
    return min;
}

int solution(int k, int n, vector<vector<int>> reqs) {
    int answer = 0;
    int left = n-k;
    vector<int> num_tutors;
    for(int i=0; i<k; ++i)
    {
        num_tutors.push_back(1);
    }
    
    while(left>=0)
    {
        answer = 0;
        int max_delay = 0;
        int index = 0;

        for(int i=0; i<k; ++i)
        {
            vector<int> q;
            int total_delay = 0;
            int num = num_tutors[i];
            for(int j=0; j<reqs.size(); ++j)
            {
                if(reqs[j][2]!=(i+1)) continue;
                if(num>0)
                {
                    num--;
                    q.push_back(reqs[j][0]+reqs[j][1]);
                    cout << "*Start time : " << reqs[j][0] << " ~   Finish time : "  << reqs[j][0]+reqs[j][1] << endl;
                }
                else
                {
                    int s = getMin(q);
                    int f = s + reqs[j][1];
                    int delay = s - reqs[j][0];
                    if(delay < 0) delay = 0;

                    total_delay += delay;
                    q.push_back(f);
                    cout << "-Start time : " << s << " ~   Finish time : "  << f << endl;
                }
            }
            answer += total_delay;
            if(total_delay > max_delay)
            {
                max_delay = total_delay;
                index = i;
            }
        }
        num_tutors[index]++;
        left--;
    }

    return answer;
}

int main()
{
    vector<vector<int>> reqs = {{10, 60, 1}, {15, 100, 3}, {20, 30, 1}, {30, 50, 3}, {50, 40, 1}, {60, 30, 2}, {65, 30, 1}, {70, 100, 2}};
    cout << "Answer : " << solution(3, 5, reqs) << endl;
    //  [10, 60, 1], [15, 100, 3], [20, 30, 1], [30, 50, 3], [50, 40, 1], [60, 30, 2], [65, 30, 1], [70, 100, 2]];
}