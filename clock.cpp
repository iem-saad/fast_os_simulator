 #include<iostream>
 #include<unistd.h>
 using namespace std;
 
 
 
 int main()
 {

  system("tty-clock -Sra 100000000 -d 0");
  system("clear");
  cout <<"\t\t\t" << "Press any key to Exit..." << endl;
  cin.get();
    system("./dealloc_resource CLOCK");
  return 0;
 }
