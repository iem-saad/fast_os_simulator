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
#include <list>
#include <iterator>
#include <bits/stdc++.h>
#include <semaphore.h>

using namespace std;


void printMainMenu(void);
void display_running_cores(void);
void displayRunningProcs(void);
void assign_core(int );
void release_resources(char* );
void * thread_for_inter_terminal_comm(void * );
void printMainMenu(void);
void dealloc_core(int );
void * dispatcher(void *);
void scheduler(void );
void * shift_process_state(void *);
bool check_free_cores(void);

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
  Casino,
  Create,
  Delete,
  Rename,
  Calendar,
  Music
};
static const char *enum_str[] =
      { "SUDOKU", "CALCULATOR", "TICTAC", "CLOCK", "NOTEPAD", "MINESWEEPER", "PHONEBOOK", "TODO", "CASINO", "CREATE", "DELETE", "RENAME", "CALENDAR", "MUSIC"};
const int noOfMaxProc = 14;
int runningProcesses[noOfMaxProc] = {0};
long int needOfProcesses[noOfMaxProc] = {0};
int threads_per_core=2;
int** runningCores;
list<int> readyQueue;
list<int> waitingQueue;
pthread_t ptid;
pthread_t dispatch;
pthread_t shift;
sem_t semaphore;
bool kernel_mode = false;



int main(int argc, char* argv[])
{

  // system("clear");
  // system("figlet -c -t -k FAST-OS | boxes -d cat -a hc -p h8 | lolcat");
  // sleep(3);
  // system("clear");
  // system(" chmod 755 os_loading_bar.sh");
  // system("./os_loading_bar.sh");
  // system(" chmod +x ./os_logo.sh");
  // system("./os_logo.sh");
  system("rm /tmp/myfifo");
  system("notify-send 'Hi There! Welcome to FAST-OS'");
  // system("figlet Resource Allocation");
  // sleep(4);
  system("clear");
  sem_init(&semaphore, 0, 1);
  string str1;
  str1 = string(argv[1]);
  if (!str1.compare("kernel"))
  {
    kernel_mode = true;
    system("notify-send 'You Are in Kernel Mode'");
  }
  needOfProcesses[0] = 150; //suduko
  needOfProcesses[1] = 50; //calculator
  needOfProcesses[2] = 100; // TicTacToe
  needOfProcesses[3] = 900; //Clock
  needOfProcesses[4] = 100; //notepad
  needOfProcesses[5] = 150; //Minesweeper
  needOfProcesses[6] = 100; //Phonebook
  needOfProcesses[7] = 50; //To Do list
  needOfProcesses[8] = 100; //Casino
  needOfProcesses[9] = 50; //Create a File
  needOfProcesses[10] = 50; //Delete a File
  needOfProcesses[11] = 50; //Rename a File
  needOfProcesses[12] = 50; //Calendar
  needOfProcesses[13] = 50; //Music
  
  while(RAM == 0 || CORES == 0 || HDD == 0 || threads_per_core < 1)
  {
    int input =0;
    cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "++++++++++++++++ Allocation Of Resources +++++++++++++++\n";
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";
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
    cout << "Please Enter How Cores you want?(2 threads per core(not in kernel_mode)): ";
    cin >> CORES;
    if (CORES < 1)
    {
      cout << "ERROR! Not Sufficient Cores Please Allocate Atleast 1 Core\n";
      continue;
    }
    if (kernel_mode)
    {
      cout << "Please Enter No Of Threads Per Core: ";
      cin >> threads_per_core;
      if (threads_per_core < 1)
      {
        cout << "Invalid Cores Please Enter Resources Again\n";
        continue;
      }
    }
  }
  system("clear");
  int status;

 
  pthread_create(&dispatch, NULL, dispatcher , NULL);
  pthread_create(&shift, NULL, shift_process_state , NULL);
  pthread_create(&ptid,NULL,thread_for_inter_terminal_comm,NULL);

  runningCores = new int*[CORES];
  for (int i = 0; i < CORES; ++i)
    runningCores[i] = new int[threads_per_core];
  for (int i = 0; i < CORES; ++i)
    for (int j = 0; j < threads_per_core; ++j)
      runningCores[i][j] = -1;
  
  
  scheduler();
  pthread_join(ptid, NULL);
  pthread_join(dispatch, NULL);
  pthread_join(shift, NULL);

  return 0;
}


void dealloc_core(int process)
{
  for (int i = 0; i < CORES; ++i)
    for (int j = 0; j < threads_per_core; ++j)
      if (runningCores[i][j] ==  process)
      {
        runningCores[i][j] = -1;
        return;
      }
}

void assign_core(int process)
{
  for (int i = 0; i < CORES; ++i)
    for (int j = 0; j < threads_per_core; ++j)
      if (runningCores[i][j] ==  -1)
      {
        runningCores[i][j] = process;
        return;
      }
}
void display_running_cores(void)
{
  for (int i = 0; i < CORES; ++i)
    for (int j = 0; j < threads_per_core; ++j)
      if (runningCores[i][j] !=  -1)
      {
        cout << "-----------------------------------------------------------------------\n";
        cout << "Core " << i+1 << " is Executing "<< enum_str[runningCores[i][j]] <<endl;
        cout << "-----------------------------------------------------------------------\n";
      }
}


void displayRunningProcs(void)
{
  bool noProcFlag=false;
  system("tput setaf 3");
  cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
  cout << "++++++++++++++++ CURRENTLY RUNNING PROCESSES +++++++++++++++\n";
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";
  cout << "Available RAM: " << RAM <<" MB"<<endl;
  cout << "Available Storage: " << HDD <<" MB" <<endl;
  cout << "Available Cores: " << CORES <<endl<<endl;
  display_running_cores();
  for (int i = 0; i < 15; ++i)
  {
    if (runningProcesses[i])
    {
      cout<< enum_str[i] << " is Currenlty Running " << runningProcesses[i] << " times" << endl;
      noProcFlag = true;
    }
  }
  if (!noProcFlag)
  {
    cout << "Currenlty No Processes is Running :( \n";
  }
  cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
  system("tput sgr0");
}

//////////////////////////////////////////////////
///////   RELEASE ALLOCATED RESOURCES     ////////
//////////////////////////////////////////////////

void release_resources(char* str)
{
  string str1, str2;
  int index;
    for (int i = 0;i < noOfMaxProc;i++)
    {
    str1 = string(enum_str[i]);
    str2 = string(str);
    
      if (!str1.compare(str2))
      {
        index = i;
        break;
      }
    }
    system("clear");
    dealloc_core(index);
    sem_wait(&semaphore);
    runningProcesses[index]--;
    RAM += needOfProcesses[index];
    sem_post(&semaphore);
    displayRunningProcs();
    printMainMenu();
}


//////////////////////////////////////////////////
//////////////////////////////////////////////////
///  INTER TERMINAL THREAD COMMUNICATION  ////
//////////////////////////////////////////////////
//////////////////////////////////////////////////



void * thread_for_inter_terminal_comm(void * arg)
{
  int fd;
  char * myfifo = "/tmp/myfifo";
  mkfifo(myfifo, 0666); //giving permissions

  char arr1[80], arr2[80];
  while (true)
  {

    fd = open(myfifo, O_RDONLY);
    // Read from FIFO
    read(fd, arr1, sizeof(arr1));
    string temp = "notify-send '"+ string(arr1) +" Has Been Closed!'";
    system(temp.c_str());
    release_resources(arr1);
    close(fd);
  }
}

void printMainMenu()
{
  system("tput setaf 2");
  cout << "\n************************************************************\n";
  cout << "************************ MAIN MENU *************************\n";
  cout << "************************************************************\n\n";
  system("tput sgr0");
  cout << "Please Enter 1 for SUDOKU\n";
  cout << "Please Enter 2 for Calculator\n";
  cout << "Please Enter 3 for Tic Tac Toe\n";
  cout << "Please Enter 4 for Clock\n";
  cout << "Please Enter 5 for Notepad\n";
  cout << "Please Enter 6 for Minesweeper\n";
  cout << "Please Enter 7 for PhoneBook\n";
  cout << "Please Enter 8 for TO-DO List\n";
  cout << "Please Enter 9 for Casino\n";
  cout << "Please Enter 10 to Create A File" << endl;
  cout << "Please Enter 11 to Delete A File" << endl;
  cout << "Please Enter 12 to Rename A File" << endl;
  cout << "Please Enter 13 to Open Calender" << endl;
  cout << "Please Enter 14 to Play Music" << endl;
  cout << "Please Enter 15 to terminate OS" << endl;
  cout << "Enter Here: ";
  return;
}

void * shift_process_state(void * argv)
{
  int process;
  while(true)
  {
     if(!waitingQueue.empty())
     {
      if(needOfProcesses[waitingQueue.front()-1] <= RAM && check_free_cores() )
      {
        process = waitingQueue.front();
        waitingQueue.pop_front();
        readyQueue.push_back(process);
      }
     }
  }
}

void *dispatcher(void * argv)
{
  pid_t  pid;
  string temp;
  int currRun=-1;
  //thread which check the ready queue and call exec file as soon as it get recourses
  while(true)
  {
    if(!readyQueue.empty())
    {
      currRun = readyQueue.front();
      readyQueue.pop_front();
    }
    else
      currRun = -1;

    if(currRun!= -1)
    {
        runningProcesses[currRun-1]++;
        RAM -= needOfProcesses[currRun-1];
        temp = "notify-send '"+ string(enum_str[currRun-1]) +" Has been dispatched From ReadyQueue!'";
        system(temp.c_str());
        assign_core(currRun-1);
        system("clear");
        displayRunningProcs();
        printMainMenu();

    switch(currRun)
    {
        case 1: //sodoku
        {
           pid = fork();
          if (pid == -1)
          {
            cout << "Error in forking\n";
            exit(EXIT_FAILURE);
          }
          else if (!pid)
          {
          
            execl("./exec", "./exec", "./game.sh", NULL);
          }
        }
      break;
         case 2:  //Calculator
        {
          pid = fork();
          if (!pid)
          {
            //child process
            system("g++ calculator.cpp -o calculator"); //compile
            execl("./exec", "./exec", "./calculator", NULL);  //execute
          }
        }
      break;
         case 3:  //Tic Tac Toe
        { 
          pid = fork();
          if (!pid)
          {
            //child process
            system("g++ tictac.cpp -o tictac"); //compile
            execl("./exec", "./exec", "./tictac", NULL);  //execute
          }
        }
      break;
      case 4: //clock
        {
          pid = fork();
          if (!pid)
          {
            //child process
            system("g++ clock.cpp -o clock"); //compile
            execl("./exec", "./exec", "./clock", NULL); //execute
          }
        }
      break;
      case 5: //Notepad
      {
        pid = fork();
        if (!pid)
        {
          //child process
          system("g++ notepad.cpp -o notepad"); //compile
          execl("./exec", "./exec", "./notepad", NULL); //execute
        }
      }
      break;
      case 6: //Minesweeper
      {
        pid = fork();
        if (!pid)
        {
          //child process
          system("g++ minesweeper.cpp -o minesweeper"); //compile
          execl("./exec", "./exec", "./minesweeper", NULL); //execute
        }
      }
      break;
      case 7: //PhoneBook
      {
        pid = fork();
        if (!pid)
        {
          //child process
          system("g++ phonebook.cpp -o phonebook"); //compile
          execl("./exec", "./exec", "./phonebook", NULL); //execute
        }
      }
      break;
         case 8:  //To Do
      {
      
      }
      break;
      case 9:   //Casino
      {
        pid = fork();
        if (!pid)
        {
          //child process
          system("g++ casino.cpp -o casino"); //compile
          execl("./exec", "./exec", "./casino", NULL);  //execute
        }
      }
      break;
      case 10:  //create
      {
        pid = fork();
        if (!pid)
        {
          //child process
          system("g++ create.cpp -o create"); //compile
          execl("./exec", "./exec", "./create", NULL);  //execute
        }
      }
  
    break;
    case 11:  //delete
    {
        pid = fork();
        if (!pid)
        {
          //child process
          system("g++ delete.cpp -o delete"); //compile
          execl("./exec", "./exec", "./delete", NULL);  //execute
        }
    }
    break;
    case 12:  //rename
    {
        pid = fork();
        if (!pid)
        {
          //child process
          system("g++ rename.cpp -o rename"); //compile
          execl("./exec", "./exec", "./rename", NULL);  //execute
        }
    }
    break;    
    case 13:
    {
      pid = fork();
        if (!pid)
        {
          //child process
          execl("./exec", "./exec", "./calendar.sh", NULL);  //execute
        }
    }
    break;
    case 14:
    {
      pid = fork();
        if (!pid)
        {
          //child process
          execl("./exec", "./exec", "./music.sh", NULL);  //execute
        }
    }
    break;
    } //switch ends
  }
  }


}

void scheduler(void)
{
  int choice;
  while(true)
  {
    displayRunningProcs();
    printMainMenu();
    cin >> choice;
    if (choice == 15)
    {
      system("clear");
      pthread_cancel(ptid);
      pthread_cancel(dispatch);
      pthread_cancel(shift);
      cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
      cout << "---------------- Closing all Processes & Exiting ----------------\n";
      cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
      sleep(2);
      system("clear");
      system("figlet -c -t -k BYE BYE | boxes -d peek -a hc -p h8 | lolcat");
      sleep(2);
      system("killall -9 gnome-terminal-server");
      exit(0);
    }
    if (choice <= noOfMaxProc && choice >= 1)
    {
      if ((RAM >= needOfProcesses[choice-1]) && check_free_cores())
      {
          //Ready Queue Implementation
          readyQueue.push_back(choice);
      }
      else
      {
        //waiting queue implementation
        system("zenity --warning --width=400 --height=200 --text 'Ops! Not Enough RAM Available Process has been added to waiting Queue'");
        waitingQueue.push_back(choice);
        continue;
      }
    }
  } 
}

bool check_free_cores()
{
  for (int i = 0; i < CORES; ++i)
    for (int j = 0; j < threads_per_core; ++j)
      if (runningCores[i][j] ==  -1)
        return true;
  return false;
}

