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

#define SUDOKU_RAM 250;

void printMainMenu(void);
long int RAM = 0;
long int HDD = 0;
long int CORES = 0;

enum Processes {
    Sudoku,
    Calculator,
    TicTacToe,
    Clock,
    Notepad,
    Minesweeper,
    PhoneBook,
    TODO,
    Sacino
};
static const char *enum_str[] =
        { "Sudoku", "Calculator", "Tic Tac Toe", "Clock", "Notepad", "Minesweeper", "PhoneBook", "TODO", "CASINO"};
const int noOfMaxProc = 10;
bool runningProcesses[noOfMaxProc] = {0};
long int needOfProcesses[noOfMaxProc] = {0};

void displayRunningProcs(void)
{
  bool noProcFlag=false;
  cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
  cout << "++++++++++++++++ CURRENTLY RUNNING PROCESSES +++++++++++++++\n";
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";
  cout << "Available RAM: " << RAM <<" MB"<<endl;
  cout << "Available Storage: " << HDD <<" MB" <<endl;
  cout << "Available Cores: " << CORES <<endl<<endl;
  for (int i = 0; i < 3; ++i)
  {
    if (runningProcesses[i])
    {
      cout<< enum_str[i] << " is Currenlty Running\n";
      noProcFlag = true;
    }
  }
  if (!noProcFlag)
  {
    cout << "Currenlty No Processes is Running :( \n";
  }
  cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
}

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
      runningProcesses[0] = false;
      RAM += needOfProcesses[0];
      displayRunningProcs();
      printMainMenu();
    }
    // printf("DATA WAS: %s\n", arr1);
    close(fd);
  }
}

void printMainMenu()
{
  cout << "\n************************************************************\n";
  cout << "************************ MAIN MENU *************************\n";
  cout << "************************************************************\n\n";
  cout << "Please Enter 1 for SUDOKU\n";
  cout << "Please Enter 2 for Calculator\n";
  cout << "Please Enter 3 for Tic Tac Toe\n";
  cout << "Please Enter 4 for Clock\n";
  cout << "Please Enter 5 for Notepad\n";
  cout << "Please Enter 6 for Minesweeper\n";
  cout << "Please Enter 7 for PhoneBook\n";
  cout << "Please Enter 8 for TO-DO List\n";
  cout << "Please Enter 9 for Casino\n";
  cout << "Enter Here: ";
  return;
}
int main()
{

  // system(" chmod +x ./os_logo.sh");
  // system("./os_logo.sh");
  system("rm /tmp/myfifo");
  needOfProcesses[0] = 120;
  while(RAM == 0 || CORES == 0 || HDD == 0)
  {
    int input =0;
    cout << "Please Enter How Much RAM you want?(in GB's): ";
    cin >> input;
    if (input < 1)
    {
      cout << "ERROR! Not Sufficient RAM Please Allocate Atleast 1 GB\n";
      continue;
    }
    RAM = 1024*input;
    cout << "Please Enter How Much Storge you want?(in GB's): ";
    cin >> input;
    if (input < 1)
    {
      cout << "ERROR! Not Sufficient Hard Disk Please Allocate Atleast 1 GB\n";
      continue;
    }
    HDD = 1024*input;
    cout << "Please Enter How Cores you want?(2 threads per core): ";
    cin >> CORES;
    if (CORES < 1)
    {
      cout << "ERROR! Not Sufficient Cores Please Allocate Atleast 1 Core\n";
      continue;
    }
  }

  pid_t  pid;
  int choice;
  int status;
  pthread_t ptid;
  pthread_create(&ptid,NULL,thread_for_inter_terminal_comm,NULL);
  while(true)
  {
    displayRunningProcs();
    printMainMenu();
    cin >> choice;
    if (choice < noOfMaxProc && choice >= 1)
    {
      if (RAM >= needOfProcesses[choice-1])
      {
        runningProcesses[choice-1] = true;
        RAM -= needOfProcesses[choice-1];
      }
    }
    if (choice == 1)
    { 

      int ret = 1;

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

