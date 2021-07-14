#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <ctime>
#include <cstring>
using namespace std;

int main()
{
	int fd1;
	char * myfifo = "/tmp/myfifo";
	mkfifo(myfifo, 0666);

	char str1[80];
	char * str2;
	// while (1)
	// {
		// Now open in write mode and write
		// cout << "ENTER: ";
		fd1 = open(myfifo,O_WRONLY);
		// fgets(str2, 80, stdin);
		str2 = "SUDOKU";
		write(fd1, str2, strlen(str2)+1);
		close(fd1);
	// }
	return 0;
}
