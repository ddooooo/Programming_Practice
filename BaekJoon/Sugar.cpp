#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;

    cout << "Input: " << n << endl;

    int num = 0;

    if(n%5 == 0) 
    {
        num = n/5;
    }
    else
    {
        while(true)
        {
            num += 1;
            n -= 3;
            cout << "n: " << n << " and num: " << num << endl;
            
            if(n%5==0)
            {
                num += (n/5);
                break;
            }  
            else if(n == 0)
            {
                break;
            }
            else if(n<0)
            {
                num = -1;
                break;
            }
        }
    }

    cout << "Output: " << num << endl;
}