#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

int main() 
{

    ifstream vertex_file("Plane_Vertices_List.txt");

    if(!vertex_file.is_open()) 
    {
        cout << "Failed to open file" << endl;
        return 0;
    }

    string line;
    string l, x, y, z;

    while(getline(vertex_file, line))
    {
        if(line.empty()) continue;
        
        stringstream ss(line);

        getline(ss, l, ' ');

        if(l == "#") continue;

        if(l == "v") // vertex coordinates
        {
            vector<float> vert_coord;

            getline(ss, x, ' ');
            getline(ss, y, ' ');
            getline(ss, z, ' ');

            //cout <<  l << ": " << x << " " << y << " " << z << endl;

            vert_coord = {stof(x), stof(y), stof(z)};

            cout << l << ": " << vert_coord[0] << " " << vert_coord[1] << " " << vert_coord[2] << endl;

        }
        else if(l == "vn")
        {

            vector<float> normal;

            getline(ss, x, ' ');
            getline(ss, y, ' ');
            getline(ss, z, ' ');

            normal = {stof(x), stof(y), stof(z)};

            cout << l << ": " << normal[0] << " " << normal[1] << " " << normal[2] << endl;
        }
        else if (l == "f")
		{
			string index;
            cout << "Faces: ";
			while (getline(ss, index, ','))
			{
				unsigned int index_uint = stoul(index, nullptr, 0);
				cout << index_uint << " ";
			}
            cout << endl;
		}
    }

}
