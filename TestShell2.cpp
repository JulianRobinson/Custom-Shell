#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

using namespace std;
static const int BUFFSIZE = 200;
static int should_run = 1; //Flag to determine when to exit
int main(void)
{
        pid_t child_pid;
       // int should_run = 1;   /* flag to determine when to exit program */
        while (should_run)
        {
                child_pid = fork();
		
                if (child_pid < 0)
                { /* error occurred */
                        fprintf(stderr, "Fork Failed");
                        return 1;
                }
                else if (child_pid == 0)
                {       // I’m the child process, run program with parent’s I/O
                        char s1[BUFFSIZE] = {0};

                        printf("CustomShell>");
                        fflush(stdout);

                        fgets(s1, BUFFSIZE, stdin);
                        s1[strcspn(s1,"\n")] = 0;
                        char *pch = strtok(s1," ");
                        char *args[BUFFSIZE];
			

                        int i = 0;
                        while (pch != NULL)
                        {
                                args[i++] = pch;
                                pch = strtok (NULL, " ");
                        }
			
			
			string s = "exit";
			if (s == args[0])
                        {
                                printf("Ran if");
                                should_run = 0;
                                kill(getppid(), SIGINT);
				return 0;
                        }

                        int status_code = execvp(args[0],args);
                        if (status_code == -1)
                        {
                                printf("Error!");
                        }
                        return 0;
                }
                else
                {                       // I’m the parent: wait for the child to  complete
                        wait(NULL);
                        printf("Child Complete\n");
		
                }
        }
        return 0;
}

