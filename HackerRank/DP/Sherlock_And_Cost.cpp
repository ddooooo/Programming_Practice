#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int dp(vector<int> arr)
{
    int sum_min = 0;
    int sum_max = 0;
    for(int i=1; i<arr.size(); ++i)
    {
        int max_min = abs(1 - arr[i-1]);
        int min_max = abs(arr[i] - 1);
        int max_max = abs(arr[i] - arr[i-1]);
        
        int new_sum_min = max(sum_min, sum_max + max_min);
        int new_sum_max = max(sum_max + max_max, sum_min + min_max);

        sum_min = new_sum_min;
        sum_max = new_sum_max;
    }
    return max(sum_min, sum_max);
}

int main()
{
    
    int t;
    cin >> t;
    
    for(int i=0; i<t; ++i)
    {
        int n;
        cin >> n;

        vector<int> arr(n);
        for(int j=0; j<n; ++j)
        {
            int a;
            cin >> a;
            arr[j] = a;
        }
        cout << dp(arr) << endl;
    }
}