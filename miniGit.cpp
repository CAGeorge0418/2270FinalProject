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
            if(temp_s->fileName == name) return temp_s->fileVersion;
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
    
    
    
    
    #include <iostream>
#include <fstream>
#include <io.h>
#include "miniGit.hpp"

using namespace std;

// CODE FOR DIRECTORY AND ADDING/COMMITTING FILES
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

 //
    
}

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

}

void miniGit::checkout(int commitNumber)
{

}

