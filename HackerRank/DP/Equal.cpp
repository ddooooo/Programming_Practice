#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;
/*
 * Complete the 'equal' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

int equal(vector<int> arr) 
{
    int min = *min_element(arr.begin(), arr.end());
    int min_step = 99999;
    for(int i=0; i<5; ++i)
    {
        if((min-i) >= 0)
        {
            int step1 = 0;
            int step2 = 0;

            for(int j=0; j<arr.size(); ++j)
            {
                int diff1 = arr.at(j) - (min - i);
                //cout << "diff: " << diff << endl;
                step1 += diff1/5 + (diff1%5)/2 + (diff1%5)%2;
            }
            //cout << "Step: " << step << endl;
            
            if(min_step > step1)
            {
                min_step = step1;
            }
        }
    }
    
    return min_step;
}

int main()
{
    
    int t;
    cin >> t;
    
    for(int i=0; i<t; ++i)
    {
        int n;
        //cout << "Enter #" << i << " test case: " << endl;
        cin >> n;
        //cout << "Size will be " << n << endl;
        vector<int> arr(n);
        for(int j=0; j<n; ++j)
        {
            int a;
            cin >> a;
            arr[j] = a;
        }
        cout << equal(arr) << endl;
        //cout << endl;
        //cout << "size: " << arr.size() << endl;
        // for(int k=0; k<arr.size(); ++k)
        // {
        //     cout << arr.at(k) << endl;
        // }

    }
}