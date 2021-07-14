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
using namespace std;

int main()
{

  system("gnome-terminal -- sh -c './game.sh'");
  return 0;
}

