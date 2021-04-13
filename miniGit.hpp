#ifndef MINIGIT_HPP
#define MINIGIT_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
using namespace std;

struct doublyNode{
  int commitNumber;
  singlyNode* head;
  doublyNode* previous;
  doublyNode* next;
};

struct singlyNode{
  string fileName;
  string fileVersion;
  singlyNode* next;
};


class github{

};

#endif
