#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int equal(vector<int> arr) 
{
    int min = 100000;
    //cout << "size of arr " << arr.size() << " " << arr.at(arr.size()-1)<< endl;
    for(int i=0; i<arr.size(); ++i)
    {
        int num = arr[i];
        if(min > num)
        {
            min = num;
            //cout << min << " at" << i << " ";
        }
    }
    //cout << endl;
    //cout << min << endl;
    int min_step = 99999999;
    for(int i=0; i<5; ++i)
    {
        //cout << min << endl;
        if((min-i) >= 0)
        {
            int step1 = 0;
            int step2 = 0;
            int step3 = 0;            
            for(int j=0; j<arr.size(); ++j)
            {
                int diff1 = arr.at(j) - (min - i);
                int diff2 = diff1+1;
                int diff3 = diff1+2;                
                //cout << "diff " << diff << endl;
                step1 += diff1/5 + (diff1%5)/2 + (diff1%5)%2;
                step2 += diff2/5 + (diff2%5)/2 + (diff2%5)%2;
                step3 += diff3/5 + (diff3%5)/2 + (diff3%5)%2;                
            }
            
            int temp = (step1 > step2) ? step2 : step1;
            
            temp = (temp > step3) ? step3 : temp;
            
            if(min_step > temp)
            {
                min_step = temp;
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
        cin >> n;

        vector<int> arr(n);
        for(int j=0; j<n; ++j)
        {
            int a;
            cin >> a;
            arr[j] = a;
        }
        cout << equal(arr) << endl;
    }
}
