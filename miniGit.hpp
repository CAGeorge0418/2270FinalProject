#ifndef MINIGIT_HPP
#define MINIGIT_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>

using namespace std;

struct singlyNode
{
  string fileName = "";
  string fileVersion = "";
  singlyNode* next = NULL;
};

struct doublyNode
{
  int commitNumber = 0;
  singlyNode* head = NULL;
  doublyNode* previous = NULL;
  doublyNode* next = NULL;
};

class miniGit
{
  private:
  doublyNode* chief;
  doublyNode* tail;
  
  public:
  miniGit();
  ~miniGit();
  
  string addFile(string name);
  void commit();
  void removeFile(string name);
  void checkout(int commitNumber);

  doublyNode* getChief();
  doublyNode* getTail();

  doublyNode* findDNode(int commitNumber);
  void log(); 
};

#endif
