#include <iostream>
#include <string>

using namespace std;

int main()
{

    // Int to String
    int n = 10;
    string str1 = to_string(n);
    string str2 =  str1 + "100";
    cout << "Int to String: " << str2 << endl;

    // String to Int
    string str3 = "100";
    int integer = stoi(str3);
    cout << "String to Int: " << integer << endl;

}