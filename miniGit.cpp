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

void miniGit::addFile(string name)
{

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

