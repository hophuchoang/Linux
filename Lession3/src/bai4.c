#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
  
int main (void) 
{ 
    pid_t child_pid;

    child_pid = fork();

    if (child_pid == 0){ // Process con
        printf("\nIm the child process\n");
        printf("My PID is: %d, my parent PID is: %d\n", getpid(), getppid());
        sleep(1);
        exit(1);

    } else if (child_pid > 0){
        printf("\nIm the parent process\n");
        printf("My PID is: %d, my parent PID is: %d, my child PID is: %d\n", getpid(), getppid(), child_pid);
        // while (1);

        int status;
        pid_t finished_pid = wait(&status);
        printf("finished_pid: %d, WEXITSTATUS: %d, WIFEXITED: %d\n", finished_pid, WEXITSTATUS(status), WIFEXITED(status)); 

    } else {
        printf("can't create child process!");
    }
  
    return 0; 
} 