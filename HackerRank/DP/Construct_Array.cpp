#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <math.h>
using namespace std;


long ConstructArray(int n, int k, int x)
{
    // Initialize 2d dynamic programming array
    // f(i) -> the number of possible array of length i that ends with x
    // g(i) -> the number of possible array of length i that ends with 1
    vector<long long> f(n); 
    vector<long long> g(n);
    cout << "n: " << n << " k: " << k << " x: " << x << endl;
    // Base cases
    // Ends with x
    f[0] = 0;
    f[1] = 1;

    // Ends with 1
    g[0] = 1;
    g[1] = 0;

    long mod = pow(10, 9) + 7;

    //cout << mod << " " << 1000000007 <<  endl;

    for(int i=2; i<n-1; ++i)
    {
        cout << "At " << i << ": ";
        f[i] = ((k-2)*f[i-1] + g[i-1])%mod; // Ends with x
        g[i] = ((k-1)*f[i-1])%mod; // Ends with 1s
        

        cout << f[i] << " " << g[i] << endl;
    }
    
    if(x==1)
        return ((k-1)*f[n-2])%mod;
    else
        return ((k-2)*f[n-2] + g[n-2])%mod;
}


int main()
{
    int n;
    cin >> n;

    int k;
    cin >> k;

    int x;
    cin >> x;

    cout << ConstructArray(n, k, x) << endl;
}