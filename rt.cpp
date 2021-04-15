#include <iostream>
#include "miniGit.hpp"
using namespace std;

int main()
{
system("mkdir minigits");

miniGit g;

g.addFile("driver.cpp");
g.addFile("miniGit.cpp");

g.commit();





}
