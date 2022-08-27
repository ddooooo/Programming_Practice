#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <map>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    
    int n;
    int q;
    
    cin >> n;
    cin >> q;
    
    string line;
    // Read empty space string
    getline(cin,line);
    map<string, string> tags;
    int index = 0;
    int end = false;
    string pretag = "";
    while(index < n)
    {
        getline(cin, line);
        cout << "First: " << line << endl;
        
        ++index;
        // If the line is a closing tag
        if(line[1] == '/' ) 
        {
            continue;
        } 
        
        int i = 0;
        while(line[i] != ' ' && line[i] != '>')
        {
            cout << i << endl;
            cout << line[i] << endl;
            ++i;
        }

        string tag = line.substr(1, i-1);
        if(pretag == "")
        {
            pretag = tag; // First tag
        }
        else 
        {
            pretag = pretag + "." + tag;
        }
        
        cout << pretag << endl;
        if(line[i] == '>') continue;
        
        // Erase the tag from the line
        line.erase(0, ++i);

        bool end = false;
        while(!end)
        {
            cout << "Line: " << line << endl;
        
            int i = 0;
            while(line[i] != ' ') ++i;
            
            string attrib = line.substr(0, i);
            line.erase(0, i);
            
            i=0;
            while(line[i] != '\"') ++i;
            int j = ++i;
            
            while(line[i] != '\"') ++i;
            string value = line.substr(j, i-j);
            
            if(line[++i] == '>') 
            {
                cout << "line[++j] " << line[i] << endl;
                cout << "Reach end of line" << endl;
                end = true;
            }
            
            line.erase(0, ++i);
            attrib = pretag + "~" + attrib;
            cout << "Attrib: " << attrib << " " << "value: " << value << endl;
            tags[attrib] = value;
            
        }
        cout << "index: " << index << endl;
    }
    
    // Query
    for(int i=0; i<q; ++i)
    {
        string query;
        getline(cin, query);
        cout << "query: " << query << endl;
        
        string ans = tags[query];
        
        if(ans.empty())
        {
            cout << "Not Found!" << endl;
        }
        else {
            cout << ans << endl;
        }
        cout << endl;
    }
    return 0;
}
