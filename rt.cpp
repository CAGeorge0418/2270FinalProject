#include <iostream>
#include "miniGit.hpp"
using namespace std;

int main()
{
system("mkdir minigit");

miniGit g;

g.addFile("driver.cpp");
g.addFile("practice.txt");

g.commit();

int pause;
cin >> pause;

g.addFile("practice.txt");
g.addFile("driver.cpp");

g.commit();




}
    
