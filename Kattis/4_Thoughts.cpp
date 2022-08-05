#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;


int calculate(int num1, int num2, char oper)
{
    switch(oper)
    {
        case '*':
            return num1 * num2;
        
        case '/':
            return num1 / num2;

        case '+':
            return num1 + num2;

        case '-':
            return num1 - num2;
    }
    return -1;
}


int main()
{
    int nInputs;

    cin >> nInputs;

    map<int, vector<char>> eqns;
    map<int, char> ops = { {0, '*'}, {1, '/'}, {2, '+'}, {3, '-'} };
    int count = 0;
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            for(int k=0; k<4; k++)
            {
                int num = 0;
                vector<int> fours = {4, 4, 4, 4};
                vector<char> opers = {ops[i], ops[j], ops[k]};
                
                for(int ii = 0; ii < opers.size(); ii++)
                {
                    if(opers[ii] == '*' || opers[ii] == '/')
                    {
                        fours.at(ii) = calculate(fours.at(ii), fours.at(ii+1), opers.at(ii));
                        num = fours.at(ii);
                        fours.erase(fours.begin() + ii + 1);
                        opers.erase(opers.begin() + ii);
                        ii -= 1;
                    }
                }

                for(int ii = 0; ii<opers.size(); ii++)
                {
                    if(opers[ii] == '+' || opers[ii] == '-')
                    {
                        fours.at(ii) = calculate(fours.at(ii), fours.at(ii+1), opers.at(ii));
                        num = fours.at(ii);
                        fours.erase(fours.begin() + ii + 1);
                        opers.erase(opers.begin() + ii);
                        ii -= 1;
                    }
                }
                eqns[num] =  {ops[i], ops[j], ops[k]};
            }
        }
    }

    int* inputs = new int[nInputs];
    
    for(int i = 0; i<nInputs; i++)
    {
        int input;
        cin >> input; 
        inputs[i] = input;
    }

    for(int i=0; i<nInputs; i++)
    {
        if(eqns.find(inputs[i]) != eqns.end())
        {
            cout << "4 " << eqns[inputs[i]].at(0) << " 4 " << eqns[inputs[i]].at(1) << " 4 " << eqns[inputs[i]].at(2) <<  " 4 = " << inputs[i] << endl;
        }
        else
        {
            cout << "no solution" << endl;
        }
    }

    delete inputs;
    return 0;
    
}