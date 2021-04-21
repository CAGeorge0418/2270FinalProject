#include <iostream>
#include "miniGit.hpp"

using namespace std;

int main()
{
    string option = "0";
    int numopt = 0;

    miniGit mini;
    

    cout << "Welcome to MiniGit!" << endl;

    while (numopt != 5)
    {
        cout << endl;
        cout << "----- Menu -----" << endl;
        cout << "1. Add a File" << endl;
        cout << "2. Remove a File" << endl;
        cout << "3. Commit Changes" << endl;
        cout << "4. Checkout Previous Version" << endl;
        cout << "5. Quit" << endl;

        getline(cin, option);
        numopt = stoi(option);

        switch(numopt)
        {
            case 1:
            {
                string filename;
                bool found = false;
                ifstream iFile;
                cout << "Please enter the name of the file to be added:" << endl;
                while (!found)
                {
                    getline(cin, filename);
                    iFile.open(filename);
                    if (iFile.is_open())
                    {
                        found = true;
                    }
                    else
                    {
                        cout << "Please enter an existing file in the directory:" << endl;
                    }
                    iFile.close();
                }

                cout << mini.addFile(filename) << endl;

                cout << endl;

                break;
            }
            case 2:
            {
                string filename;
                cout << "Please enter the name of the file to be removed:" << endl;
                getline(cin, filename);

                mini.removeFile(filename);

                cout << endl;

                break;
            }
            case 3:
            {
                mini.commit();

                cout << endl;

                break;
            }
            case 4:
            {
                string comnum;
                bool input = false;
                cout << "Please enter the Commit Number of the desired version:" << endl;
                while (!input)
                {
                    input = true;
                    getline(cin, comnum);
                    for (int i = 0; i < comnum.length(); i++)
                    {
                        if (comnum[i] != '1' || comnum[i] != '2' || comnum[i] != '3' || comnum[i] != '4' || comnum[i] != '5' || comnum[i] != '6' || comnum[i] != '7' || comnum[i] != '8' || comnum[i] != '9' || comnum[i] != '0')
                        {
                            cout << "Please enter a positive integer" << endl;
                            input = false;
                        }
                    }
                }
                mini.checkout(stoi(comnum));

                cout << endl;

                break;
            }
            case 5:
            {
                cout << "Goodbye!" << endl;
                break;
            }
            default:
            {
                cout << "Please enter a number between 1 and 5." << endl;
                break;
            }
        }

    }
}
