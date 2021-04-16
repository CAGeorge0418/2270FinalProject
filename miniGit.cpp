#include <iostream>
#include <fstream>
#include "miniGit.hpp"

using namespace std;


miniGit::miniGit()
{
    chief = new doublyNode;
    chief->commitNumber = 0;
}

miniGit::~miniGit()
{
    doublyNode* tmp_d = chief;

    while (tmp_d != NULL)
    {
        singlyNode* temp_s = chief->head;

        while (temp_s != NULL)
        {
            chief->head = chief->head->next;
            delete temp_s;
            temp_s = chief->head;
        }
        chief = chief->next;
        delete tmp_d;
        tmp_d = chief;
    }
}

string traverseGit(string name, doublyNode* chief)
{
    doublyNode* tmp_d = chief;

    while (tmp_d != NULL)
    {
        singlyNode* temp_s = tmp_d->head;

        while (temp_s->next != NULL)
        {
            temp_s = temp_s->next;
            if (temp_s->fileName == name) 
            {
                //makes integer of file number, iterates it and returns in the correct format
                int holder = stoi(temp_s->fileVersion);
                holder++;
                if (holder >9) return to_string(holder);
                else return "0" + to_string(holder);

            }
        }
        tmp_d = tmp_d->next;
    }

    return "00";
}

string miniGit::addFile(string name)
{
    //checks if file exists in directory
    ifstream newbie;
    newbie.open(name);
    if (!newbie.is_open()) return "File does not exist in directory";
    newbie.close();

    //creates temporary variables
    singlyNode* tmp_s = NULL;
    doublyNode* tmp_d = chief;
    //youll hate me for this but it helps counteract a seg fault
    bool quit = false;
    

    //locates the most current double node
    while (tmp_d->next != NULL) tmp_d = tmp_d->next;
    
    //if the head doesnt exist make it
    if (tmp_d->head == NULL)
    {
        tmp_s = new singlyNode;
        tmp_d->head = tmp_s;
        tmp_s->fileName = name;
        tmp_s->next = NULL;
        quit = true;
    }
    
    else tmp_s = tmp_d->head;

    //finds version in the list
    string version = traverseGit(name, chief);


    if (quit == true) 
    {
        tmp_s->fileVersion = name.substr(0,name.size()-4) + "_" + version + name.substr(name.size()-4, 4);
        return "File successfully added";
    }

    //gets to the most recent node in list
    while (tmp_s->next != NULL) 
    {
        if (tmp_s->fileName == name) return "File has already been added";
        tmp_s = tmp_s->next;
    }

    singlyNode* adding = new singlyNode;
    adding->fileName = name;
    adding->fileVersion = name.substr(0,name.size()-3) + "_" + version + name.substr(name.size()-3, 3);
    adding->next = NULL;

    tmp_s->next = adding;

    return "File successfully added";
}

void miniGit::removeFile(string name)
{
    doublyNode* tmp_d = chief;
    while (tmp_d->next != NULL) tmp_d = tmp_d->next;

    singlyNode* tmp_s = tmp_d->head;

    //if the head node in SLL is the one to delete
    if (tmp_s->fileName == name)
    {
        singlyNode* holder = tmp_s;
        tmp_s = tmp_s->next;
        delete holder;
        holder = NULL;
    }

    //otherwise
    singlyNode* prev;
    bool deleted =  false;

    while (tmp_s->next != NULL && deleted == false) 
    {
        prev = tmp_s;
        tmp_s = tmp_s->next;

        if(tmp_s->fileName == name)
        {
            prev->next = tmp_s->next;
            delete tmp_s;
            tmp_s = NULL;
            deleted = true;
        }
    }
}

//need to maintain commit numbe before adding- make that change
void miniGit::commit()
{
    doublyNode* tmp_d = chief;
    while (tmp_d->next != NULL) tmp_d = tmp_d->next;

    singlyNode* tmp_s = tmp_d->head;
    ifstream ifile;

    while (tmp_s != NULL)
    {
        string versionHolder = tmp_s->fileVersion;
        ifile.open("minigit/" + versionHolder);

        //file is not in minigit- must add it
        if (!ifile.is_open())
        {
        ifile.close();
        ifile.open(tmp_s->fileName);

        ofstream ofile;
        ofile.open("minigit/" + versionHolder);
        string line = "";
        while (getline(ifile, line)) ofile << line << endl;
        cout << "Added to the minigit" << endl;
        
        ofile.close();
        ifile.close();
        }

        //file is in minigit
        else
        {
           ifstream oldVersion;

            //finds correct version name for previous version
           string name = tmp_s->fileName;
           string oldv = traverseGit(name,chief);
           int oldv_int = stoi(oldv)-1;

           oldVersion.open("minigit/"+ name.substr(0,name.size()-3) + "_" + to_string(oldv_int) + name.substr(name.size()-3, 3));

           string old_comp = "";
           string new_comp = "";
           string line = "";

            //creates a string that contains all of the old version to compare
           while (getline(oldVersion, line))
            {
                old_comp = old_comp + line;
            }

            line = "";

            while (getline(ifile, line))
            {
                new_comp = new_comp +line;
            }

            if (old_comp != new_comp)
            {
                ofstream ofile;
                ofile.open("minigit/" + tmp_s->fileVersion);
                string line = "";
                while (getline(ifile, line))
                {
                    ofile << line << endl;
                }
                ofile.close();
            }

            oldVersion.close();
   
        }

        tmp_s = tmp_s->next;
        

    }

ifile.close();

}

void miniGit::checkout(int commitNumber)
{
    doublyNode* dNode = findDNode(commitNumber);

    if (dNode == NULL)
    {
        cout << "Could not find the version with Commit Number " << commitNumber << endl;
        return;
    }
    else
    {  
        singlyNode* curr = dNode->head;

        while (curr != NULL)
        {
            // stuff stuff stuff
            // prolly writing to files and copying to current files

            curr = curr->next;
        }
    }
}

doublyNode* miniGit::findDNode(int commitNumber)
{
    doublyNode* curr = chief;

    while (curr != NULL)
    {
        if (curr->commitNumber == commitNumber)
        {
            return curr;
        }

        curr = curr->next;
    }

    cout << "Could not find DoublyNode" << endl;
    return NULL;

}
