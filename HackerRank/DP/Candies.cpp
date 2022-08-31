#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    
    vector<int> arr(n);
    vector<int> candies(n, 1);
    for(int i=0; i<n; ++i)
    {
        int integer;
        cin >> integer;
        arr[i] = integer;
    }
    int m = 0;
    for(int i=1; i<n; ++i)
    {
        if(arr[i] > arr[i-1])
        {
            if(arr[i] > m) m = arr[i];
            
            candies[i] = candies[i-1] + 1;
        }
    }
    
    for(int i=n-2; i>=0; --i)
    {
        if(arr[i] > arr[i+1] && candies[i] <= candies[i+1])
        {
            candies[i] = candies[i+1] + 1;
        }
    }
    
    int sum = 0;
    for(int i=0; i<n; ++i)
    {
        //cout << candies[i] << " ";
        sum += candies[i];
    }
    
    cout << sum << endl;
}