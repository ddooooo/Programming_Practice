#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Solution by recursion
int recursion(string str, int i, int j)
{
    //cout << "i and j " << i << " and " << j << " => " << str << endl; 
    //cout << "Recursion at " << str << endl;
    // Base case #1: if length of str is 1
    if(i == j)
    {
        //cout << "Base #1" << endl;
        return 1;
    }

    // Base case #2: if length of str is 2
    if( j == i+1 && str[i] == str[j])
    {
        return 2;
    }
    
    int result = 0;

    if(str[i] == str[j])
    {
        int n_pos = j - i -1;
        string new_str = str.substr(i+1, n_pos); // substr (pos, npos)
        //cout << "From " << i+1 << " to " << n_pos << " " << new_str << endl;
        result = recursion(new_str, 0, n_pos-1) + 2;
    }
    else
    {
        int n_pos = j - i;
        string str_1 = str.substr(i, n_pos);
        //cout << "From " << i << " to " << n_pos-1 << " " << str_1 << endl;
        int result_1 = recursion(str_1, 0, n_pos-1);


        string str_2 = str.substr(i+1, n_pos);
        //cout << "From " << i+1 << " to " << n_pos << " " << str_2 << endl;
        int result_2 = recursion(str_2, 0, n_pos-1);
        result = max(result_1, result_2);
    }

    return result;
}

// Solution by dynamic programming
int PlayWithWords(string s)
{
    int n = s.size();
    vector<vector<int>> t(n);
    for(int i=0; i<n; ++i)
    {
        t[i] = vector<int>(n);
        t[i][i] = 1;
    }

    

    for(int l=2; l<=n; ++l)
    {
        for(int i=0; i<n-(l-1); ++i)
        {
            int j = i + l - 1;
            if(s[i] == s[j] && l == 2)
            {
                t[i][j] = 2;
                //cout << t[i][j] << endl;
            }
            else if(s[i] == s[j])
            {
                t[i][j] = 2 + t[i+1][j-1];
                //cout << t[i][j] << endl;
            }
            else
            {
                t[i][j] = max(t[i][j-1], t[i+1][j]);
                //cout << t[i][j] << endl;
            }
        }
    }


    int m = 0;
    for(int i=0; i<n-1; ++i)
    {
        int temp = t[0][i]*t[i+1][n-1];

        //cout << temp << endl;

        if(temp > m) m = temp;
    }

    return m;
}

int main()
{
    string s;
    
    getline(cin, s);    
    int result1 = 0;
    int result2 = 0;

    int m = 0;
    int n = s.size();

    if(n == 1)
    {
        cout << 1 << endl;
        return 0;
    }

    cout << endl;
    cout << "Result: " << PlayWithWords(s) << endl;

}

//eeegeeksforskeeggeeks