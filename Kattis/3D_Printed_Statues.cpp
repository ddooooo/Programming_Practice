#include <iostream>
#include <cstring>
using namespace std;


// Make printer until the number of printer is greater or equal to the number of 3D model to build

int main()
{
    int nStatues;
    
    cin >> nStatues;

    int nPrinter = 1;
    int nPrevious = 1;
    int nDays = 1;
    

    while( nPrinter < nStatues)
    {
        nPrinter += nPrevious;
        nPrevious = nPrinter;
        nDays++;
    }

    cout << nDays;
    return 0;
}