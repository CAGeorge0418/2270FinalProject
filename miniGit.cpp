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

}

void miniGit::removeFile(string name)
{

}

void miniGit::commit()
{

}

void miniGit::checkout(int commitNumber)
{

}

