#include <iostream>
#include <fstream>
#include "miniGit.hpp"

using namespace std;


miniGit::miniGit()
{
    chief->commitNumber = 0;
    chief->head = NULL;
    chief->previous = NULL;
    chief->next = NULL;
}

miniGit::~miniGit()
{
    doublyNode* tmp_d = chief;

    while(tmp_d != NULL)
    {
        singlyNode* temp_s = chief->head;

        while(temp_s != NULL)
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

    while(tmp_d != NULL)
    {
        singlyNode* temp_s = tmp_d->head;

        while(temp_s != NULL)
        {
            temp_s = temp_s->next;
            if(temp_s->fileName == name) 
            {
                //makes integer of file number, iterates it and returns in the correct format
                int holder = stoi(temp_s->fileVersion);
                holder++;
                if(holder >9) return to_string(holder);
                else return "0" + to_string(holder);

            }
        }
        tmp_d = tmp_d->next;
    }

    return "00";
}

string miniGit::addFile(string name)
{
    ifstream newbie;
    newbie.open(name);
    if(!newbie.is_open()) return "File does not exist in directory";
    newbie.close();

    doublyNode* tmp_d;

    while(tmp_d->next != NULL) tmp_d = tmp_d->next;

    singlyNode* tmp_s = tmp_d->head;

    while(tmp_s->next != NULL) 
    {
        if(tmp_s->fileName == name) return "File has already been added";
        tmp_s = tmp_s->next;
    }

    singlyNode* adding = new singlyNode;
    adding->fileName = name;
    string version = traverseGit(name, chief);
    adding->fileVersion = name.substr(0,name.size()-3) + "_" + version + name.substr(name.size()-3, 3);
    adding->next = NULL;

    tmp_s->next = adding;

    return "File successfully added";

}

void miniGit::removeFile(string name)
{
    doublyNode* tmp_d;
    while(tmp_d->next != NULL) tmp_d = tmp_d->next;

    singlyNode* tmp_s = tmp_d->head;

    //if the head node in SLL is the one to delete
    if(tmp_s->fileName == name)
    {
        singlyNode* holder = tmp_s;
        tmp_s = tmp_s->next;
        delete holder;
        holder = NULL;
    }

    //otherwise
    singlyNode* prev;
    bool deleted =  false;

    while(tmp_s->next != NULL && deleted == false) 
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

void miniGit::commit()
{
    doublyNode* tmp_d;
    while(tmp_d->next != NULL) tmp_d = tmp_d->next;

    singlyNode* tmp_s = tmp_d->head;
    ifstream ifile;

    while(tmp_s->next != NULL)
    {
        string versionHolder = tmp_s->fileVersion;
        ifile.open("minigit/" + versionHolder);

        //file is not in minigit- must add it
        if(!ifile.is_open())
        {
        ofstream ofile;
        ofile.open("minigit/"+ versionHolder);
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

            while(getline(ifile, line))
            {
                new_comp = new_comp +line;
            }

            if(old_comp != new_comp)
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
        

    }

ifile.close();

}

void miniGit::checkout(int commitNumber)
{

}

