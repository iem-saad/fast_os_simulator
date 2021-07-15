//Author: Saad Abdullah | Mahnoor Abid | Bilal Haider
//Operating SYSTEM Program
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <ctime>
#include <cstring>

using namespace std;

int main(int argc, char* argv[])
{
  string temp; 
  temp = "gnome-terminal -- sh -c '" + string(argv[1])  + "'"; 
  system(temp.c_str());
  return 0;
}

