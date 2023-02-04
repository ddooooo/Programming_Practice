#include <iostream>
#include <cstring>

using namespace std;

int** FlipDiagonal(int** arr)
{
    int** flip = new int*[4];
    
    // Copy all data from arr to result array
    for(int i=0; i<4; i++)
    {
        flip[i] = new int[4];
        for(int j=0; j<4; j++)
        {
            flip[i][j] = arr[j][i];
        }
    }

    return flip;
}

void FlipHorizontal(int**& arr)
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<2; j++)
        {
            int temp = arr[i][j];
            arr[i][j] = arr[i][3-j];
            arr[i][3-j] = temp;
        }
    }
}

int** recursion(int** arr, int track[][4])
{

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            cout << arr[i][j];
            if(j != 3) cout << " ";
        }
        if(i != 3) cout << endl;
    }

    cout << endl;
    cout << endl;
    // Create 2D array to store a result
    int** result = new int*[4];
    
    // Copy all data from arr to result array
    for(int i=0; i<4; i++)
    {
        result[i] = new int[4];
        for(int j=0; j<4; j++)
        {
            result[i][j] = arr[i][j];
        }
    }

    for(int i = 0; i<4; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(result[i][j] == 0)
            {
                result[i][j] = result[i][j+1];
                result[i][j+1] = 0;
                track[i][j] = track[i][j+1];
            }
            else if(result[i][j] == result[i][j+1] && (track[i][j] == 0 && track[i][j+1] == 0) )
            {
                result[i][j] *= 2;
                result[i][j+1] = 0;
                track[i][j]++;
            }
        }
    }

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(result[i][j] != arr[i][j])
            {
                return recursion(result, track);            
            }
        }
    }

    return result;
}

int main()
{
    int** inputArray = new int*[4];
    int inputDir;

    for(int i=0; i<4; i++)
    {
        inputArray[i] = new int[4];
        for(int j=0; j<4; j++)
        {
            cin >> inputArray[i][j];
        }
    }

    cin >> inputDir;

    switch(inputDir)
    {
        case 0: 
            break;
        case 1:
            cout << "Flip Diagonal!" << endl;
            inputArray = FlipDiagonal(inputArray);
            break;
        case 2:
            FlipHorizontal(inputArray);
            break;
        case 3:
            inputArray = FlipDiagonal(inputArray);
            FlipHorizontal(inputArray);
            break;
        default:
            break;
    }

    int track[4][4];
    memset(track, 0, sizeof(track));

    inputArray = recursion(inputArray, track);

    switch(inputDir)
    {
        case 0: 
            break;
        case 1:
            cout << "Up!" << endl;
            inputArray = FlipDiagonal(inputArray);
            break;
        case 2:
            cout << "Right!" << endl;
            FlipHorizontal(inputArray);
            break;
        case 3:
            cout << "Down!" << endl;
            FlipHorizontal(inputArray);
            inputArray = FlipDiagonal(inputArray);
            break;
        default:
            break;
    }

    cout << endl;
    cout << "Final Result : " << endl;

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            cout << inputArray[i][j];
            if(j != 3) cout << " ";
        }
        if(i != 3) cout << endl;
    }

}