#include <iostream>
#include "miniGit.hpp"

using namespace std;

int main()
{
    string option = "0";
    int numopt = 0;

    miniGit mini;

    doublyNode* curr = mini.getChief();
    
    cout << "Welcome to MiniGit!" << endl;

    while (numopt != 8)
    {
        cout << endl;
        cout << "----- Menu -----" << endl;
        cout << "1. Add a File" << endl;
        cout << "2. Remove a File" << endl;
        cout << "3. Commit Changes" << endl;
        cout << "4. Checkout Another Version" << endl;
        cout << "5. Checkout Previous Commit" << endl;
        cout << "6. Return to the Head of MiniGit" << endl;
        cout << "7. Log of Previous Commits" << endl;
        cout << "8. Quit" << endl;


        getline(cin, option);
        if (option != "1" && option != "2" && option != "3" && option != "4" && option != "5" && option != "6" && option != "7" && option != "8")
        {
            option = "0";
        }
        

        numopt = stoi(option);

        switch(numopt)
        {
            case 1:
            {
                if (curr != mini.getTail())
                {
                    cout << "Cannot add a file while checking out an older version" << endl;
                    break;
                }
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
                if (curr != mini.getTail())
                {
                    cout << "Cannot remove a file while checking out an older version" << endl;
                    break;
                }
                string filename;
                cout << "Please enter the name of the file to be removed:" << endl;
                getline(cin, filename);

                mini.removeFile(filename);

                cout << endl;

                break;
            }
            case 3:
            {
                if (curr != mini.getTail())
                {
                    cout << "Cannot commit while checking out an older version" << endl;
                    break;
                }

                mini.commit();

                curr = mini.getTail();

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
                        if (comnum[i] != '1' && comnum[i] != '2' && comnum[i] != '3' && comnum[i] != '4' && comnum[i] != '5' && comnum[i] != '6' && comnum[i] != '7' && comnum[i] != '8' && comnum[i] != '9' && comnum[i] != '0')
                        {
                            cout << "Please enter a positive integer" << endl;
                            input = false;
                        }
                    }
                }

                bool checked = mini.checkout(stoi(comnum));

                if (checked)
                {
                    curr = mini.findDNode(stoi(comnum));
                }

                cout << endl;

                break;
            }
            case 5:
            {
                mini.checkout(mini.getTail()->commitNumber - 2);

                curr = mini.getTail()->previous->previous;
                
                break;
            }
            
            case 6:
            {
                mini.checkout(mini.getTail()->commitNumber);

                curr = mini.getTail();
                cout << "Returning to the head of MiniGit" << endl; 
                break;
            }
            case 7:
            {
                cout << "Here is the current log of MiniGit:" << endl;
                cout << "-----------------------------------" << endl;
                mini.log();

                break;
            }
            case 8:
            {
                cout << "Goodbye!" << endl;
                break;
            }

            default:
            {
                cout << "Please enter a number between 1 and 6" << endl;
                break;
            }
        }

    }
}
