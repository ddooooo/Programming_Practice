#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Find a Palindromic Substring by using dynamic programming

int playWithWords(string s) {
    
    // Initialize 2d dynamic array
    int size = s.size();
    int** table = new int*[size];
    for(int i=0; i<size; ++i)
    {
        table[i] = new int[size];
    } 

    int max = 1;

    // Initial Conditions
    for(int i=0; i<size; ++i)
    {
        table[i][i] = 1;
        if(s[i] == s[i+1]) 
        {
            table[i][i+1] = 2;
        }
        else
        {
            table[i][i+1] = -1;
        }
    }

    // Set up a table with dynamic programming
    for(int l=3; l<=size; ++l) // l --> a size of substring
    {
        for(int i=0; i<size-(l-1); ++i)
        {
            int j = i + (l-1);
            if(table[i+1][j-1] > 0 && s[i] == s[j])
            {
                table[i][j] = l;
            }
            else 
            {
                table[i][j] = -1;    
            }
        }
    }
    int a_max = 0;
    int b_max = 0;
    for(int i=0; i<size; ++i)
    {
        for(int j=i; j<size-1; ++j)
        {
            int a = table[i][j];
            int b = table[j+1][size-1];
            int score = a * b;
            
            //printf("At (%d, %d)   =>    %d * %d \n", i, j, a, b );
            
            if(score > max)
            {
                max = score;
            }
        }
    }
    
    // Deallocate the array
    for(int i=0; i<size; ++i)
    {
        delete[] table[i];
    }

    return max;    
}

int main()
{
    string str;

    cout << "Enter input: \n";
    getline(cin, str);

    int result = playWithWords(str);

    cout << result << "\n";

    return 0;
}
