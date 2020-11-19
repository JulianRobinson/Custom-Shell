# Custom-Shell
Custom Command Line Linux Shell written in C++

I have included all working versions of the shell as it was being implemented. 
myShell2020.cpp is the final working version. 
Compile and execute, then enter commands including a pipe such as "ls -l | wc" or "TestShell2.cpp | wc -l"
Upon entering "exit" the program terminates.

This Custom Shell utilizes functions and system calls including fork(), execvp(), and dup2() to execute both commands on either side of the pipe.
