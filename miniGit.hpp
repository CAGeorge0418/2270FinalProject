#ifndef MINIGIT_HPP
#define MINIGIT_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>

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
  private:
  doublyNode head;
  
  
  public:
  github();
  ~github();
  
  void addFile(string name);
  void commit();
  void removeFile(string name);
  void checkout(int commitNumber);
  
  
  
  
  
  
};

#endif
