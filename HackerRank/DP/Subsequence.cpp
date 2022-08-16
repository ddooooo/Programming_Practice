#include <iostream>
#include <string>

using namespace std;

// Solution by recursion
int recursion(string str, int i, int j)
{
    //cout << "i and j " << i << " and " << j << " => " << str << endl; 
    // Base case #1: if length of str is 1
    if(i == j)
    {
        //cout << "Base #1" << endl;
        return 1;
    }

    // Base case #2: if length of str is 2
    if(i == j+1 && str[i] == str[j])
        return 2;
    
    int result;

    if(str[i] == str[j])
    {
        int n_pos = j - i -1;
        string new_str = str.substr(i+1, n_pos); // substr (pos, npos)
        //cout << "From " << i+1 << " " << j-1 << " " << new_str << endl;
        result = recursion(new_str, 0, n_pos-1) + 2;
    }
    else
    {
        int n_pos = j - i;
        string str_1 = str.substr(i, n_pos);
        //cout << "From " << str[i] << " to " << str[j-1] << " " << str_1 << endl;
        int result_1 = recursion(str_1, 0, n_pos-1);

        string str_2 = str.substr(i+1, n_pos);
        //cout << "From " << str[i+1] << " to " << str[j] << " " << str_2 << endl;
        int result_2 = recursion(str_2, 0, n_pos-1);
        result = max(result_1, result_2);
    }

    return result;
}

int main()
{
    string str;

    cout << "Enter input: \n";
    getline(cin, str);
    int str_size = str.size()-1;
    int result = recursion(str, 0, str_size);

    cout << endl;

    cout << "Result: " << result << endl;
}