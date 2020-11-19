#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>


using namespace std;
static const int BUFFSIZE = 200;
const int READ = 0, WRITE = 1;

int main(int argc , char *argv[]) {

/*
	While loop: either takes in a function returning 1 or 0
	this function reads and parses stdin by line
	or checks for stdin != "exit"

	
*/
while(true)
{

	char input[BUFFSIZE] = {0};
	
	printf("myShell>");
        fflush(stdout);

        fgets(input, BUFFSIZE, stdin);
	
        input[strcspn(input,"\n")] = 0;
	char exitCom[] = "exit";
	
// -----TECHNICALLY DOESNT WORK, COMPARES POINTERS, SO IF FIRST LETTER OF STRING IS "e" IT QUITS-----
	if(*input == *exitCom)
	{
		printf("Exit command recieved.\n");
		return 0;
		//kill(getpid(), SIGINT);
	}

        char *p1 = strtok(input," ");
 	char *args1[BUFFSIZE];
	char *p2;
	char *args2[BUFFSIZE];
	

	int i = 0;
	string pipeChar = "|";
	while(p1 != NULL)
	{
		if(p1 == pipeChar)
		{
			args1[strcspn(*args1,"|")] = NULL;
			p2 = strtok(NULL, "| ");
			//printf("p2 after strtok in if: %s\n", p2);
			int j = 0;
			while(p2 != NULL)
			{
				args2[j++] = p2;
				//printf("Args2 in loop: %s\n ", args2);
				//printf("p2: %s\n", p2);
				p2 = strtok(NULL, " ");
			}
			p1 = NULL;
			
		}
		else
		{
		args1[i++] = p1;
		p1 = strtok(NULL, " ");
		}

	}
	/*
	printf("p2: %s\n",p2);
	printf("args1[0]: %s\n", args1[0]);
	printf("args1[1]: %s\n", args1[1]);
	printf("args2[0]: %s\n", args2[0]);
	//cout<<"p1: "<<*p1<<endl<<"args1: "<<*args1<<endl;
	//cout<<"p2: "<<*p2<<endl<<"args2: "<<*args2<<endl;
	*/

   int pipefd[2];

   if (pipe(pipefd)  == -1) {
      std::cerr << "Error creating pipe\n";
      return 1;
   }
   int pid2 = -1, pid1 = -1;
   pid1 = fork();
   if (pid1 == 0) {
	//printf("First fork\n");
      close (pipefd[READ]);
	 dup2(pipefd[WRITE], WRITE);
      //execlp("ls", "ls", "-l", nullptr);
     int check = execvp(args1[0], args1);
	if(check == -1)
	{
		printf("Error 1!");
	}	
   }
   else {
       pid2 = fork();
       if (pid2 == 0) {
		//printf("Second fork\n ");
           close(pipefd[WRITE]);
           dup2(pipefd[READ], READ);
           //execlp("wc", "wc", "-l", nullptr);
           int check2 = execvp(args2[0], args2);
		if(check2 == -1)
		{
			printf("Error 2!");
		} 
      }
   }
   //waitpid(pid1, nullptr, 0);
     waitpid(pid1, 0, 0);

   close(pipefd[WRITE]);
   //waitpid(pid2, nullptr, 0);
   waitpid(pid2, 0, 0); 

}
return 0;

}
