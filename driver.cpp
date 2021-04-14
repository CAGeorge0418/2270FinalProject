#include <iostream>
#include <fstream>
#include <io.h>
#include "miniGit.hpp"

using namespace std;

int main()
{
    mkdir("minigit");
    string filename;
    cout << "input filename:" << endl;
    getline(cin, filename);
    ifstream ifile;
    ifile.open(filename);

    if (!ifile.is_open())
    {
        cout << "could not open " << filename << endl;
    }
    else
    {
        ofstream ofile;
        ofile.open("minigit/driver01.cpp");
        string line = "";
        while (getline(ifile, line))
        {
            ofile << line << endl;
        }
        cout << "done" << endl;
        
        ofile.close();
        ifile.close();
    }

    
    
}
