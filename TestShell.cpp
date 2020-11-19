/**
 * CustomShell.cpp
 */


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <string.h>

using namespace std;

int main()
{
pid_t pid;
	/* fork a child process */
	pid = fork();

	if (pid < 0) { /* error occurred */ 
		fprintf(stderr, "Fork Failed"); 
		return 1;
	}
	else if (pid == 0) { /* child process */
		static const int BUFFER = 200;
		char input[BUFFER] = {0};
		cout << "CustomShell>";

		fgets(input, BUFFER, stdin);
		input[strcspn(input, "\n")] = 0;		
		char *pch = strtok(input, " ");
		char *args[BUFFER];
		int i = 0;		

		while(pch != NULL)
		{
			args[i++] = pch;
			pch = strtok(NULL, " ");
		}
 
   		 printf("Before calling execvp()\n");
 
    		// Calling the execvp() system call
   		 int status_code = execvp(args[0], args);
 
    		if (status_code == -1) {
       		 printf("Process did not terminate correctly\n");
       		return 0;
   		 }
 
   		 printf("This line will not be printed if execvp() runs correctly\n");
		}
	else { /* parent process */
		/* parent will wait for the child to complete */
		wait(NULL);
		printf("Child Complete");
	}

	return 0;
}
