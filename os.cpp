//Author: Saad Abdullah | Mahnoor Abid | Bilal Haider
//Operating SYSTEM Program
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <ctime>
using namespace std;

void * thread_for_inter_terminal_comm(void * arg)
{
  int fd;
  char * myfifo = "/tmp/myfifo";
  mkfifo(myfifo, 0666);

  char arr1[80], arr2[80];
  while (true)
  {

    fd = open(myfifo, O_RDONLY);

    // Read from FIFO
    read(fd, arr1, sizeof(arr1));
    if (!strcmp(arr1 ,"SUDOKU"))
    {
      system("clear");
      cout << "DEALLOCATED";
    }
    // printf("DATA WAS: %s\n", arr1);
    close(fd);
  }
}

int main()
{

  // system(" chmod +x ./os_logo.sh");
  // system("./os_logo.sh");
  system("rm /tmp/myfifo");
  pid_t  pid;
  int choice;
  int status;
  pthread_t ptid;
  pthread_create(&ptid,NULL,thread_for_inter_terminal_comm,NULL);
  while(1)
  {
    cout << "Please Enter 1 for sduko\n";
    cout << "Enter Here: ";
    cin >> choice;
    if (choice == 1)
      { int ret = 1;
       pid = fork();
       if (pid == -1)
       {
          cout << "Error in forking\n";
          exit(EXIT_FAILURE);
       }
       else if (!pid)
       {
      
          // pid == 0 means child process created
          char * args[] = {"./exec",NULL};
          execvp(args[0],args);
          // system("gnome-terminal -- sh -c './game.sh'");
          exit(0);
       }
       else
       {
        // while(1)
        // {
        //   pid_t result = waitpid(pid, &status, WNOHANG);
        //   if (result == 0) {
        //     cout << "CHILD Present";
        //   } else if (result == -1) {
        //     // Error 
        //   } else {
        //     cout << "CHILD EXITED";
        //   }
        // }
       }
    }
    else
      cout << "Invalid Choice Please Try Again.";

  }
  pthread_join(ptid, NULL);
  return 0;
}

