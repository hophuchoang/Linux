#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define MSG_SIZE 50
  
int main (void) 
{ 
    pid_t child_pid;
    int fds[2];

    if (pipe(fds) < 0){
        printf("pipe() unsuccessfuly\n");
        exit(1);
    }

    child_pid = fork();

    if (child_pid == 0){
        if (close(fds[1]) == -1){
            printf("close fds[1] failed\n");
        }

        pid_t child_pid1;
        int fds1[2];

        if (pipe(fds1) < 0){
            printf("pipe() 1 unsuccessfuly\n");
            exit(1);
        }

        child_pid1 = fork();

        if (child_pid1 == 0){ // Process con
            if (close(fds1[1]) == -1){
                printf("close fds[1] failed\n");
            }

            while (1)
            {
                char rbuff[MSG_SIZE] = {0};
                int num_read = read(fds1[0], rbuff, MSG_SIZE);
                if (num_read == -1){
                    printf("read() failed\n");
                    exit(0);
                }
                else if (num_read == 0){
                    printf("pipe end of pipe\n");
                    break;
                }
                else{
                    printf("msg: %s\n", rbuff);
                }
            };

        }else if (child_pid1 > 0){ // process cha
            // close read fds
            if (close(fds1[0]) == -1){
                printf("close fds1[0] failed\n");
            }

            while (1)
            {
                char rbuff[MSG_SIZE] = {0};
                int num_read = read(fds[0], rbuff, MSG_SIZE);
                if (num_read == -1){
                    printf("read() failed\n");
                    exit(0);
                }
                else if (num_read == 0){
                    printf("pipe end of pipe\n");
                    break;
                }
                else{
                    strcat(rbuff, " process 1");
                    write(fds1[1], rbuff, MSG_SIZE);
                }
            };

            if (close(fds1[1]) == -1){
                printf("close fds1[1] failed\n");
            }

            int status;
            pid_t finished_pid = wait(&status);
            printf("finished_pid: %d, WEXITSTATUS: %d, WIFEXITED: %d\n", finished_pid, WEXITSTATUS(status), WIFEXITED(status)); 

        }else {
            printf("can't create child process 1!");
        }

    } else if (child_pid > 0){
        // printf("\nIm the parent process\n");
        // printf("My PID is: %d, my parent PID is: %d, my child PID is: %d\n", getpid(), getppid(), child_pid);
        // while (1);

        if (close(fds[0]) == -1){
            printf("close fds[0] failed\n");
        }

        int num_write = 0;
        while (num_write < 5)
        {
            write(fds[1], "msg from parent", MSG_SIZE);
            num_write += 1;
        }
        
        if (close(fds[1]) == -1){
            printf("close fds[1] failed\n");
        }

        int status;
        pid_t finished_pid = wait(&status);
        printf("finished_pid: %d, WEXITSTATUS: %d, WIFEXITED: %d\n", finished_pid, WEXITSTATUS(status), WIFEXITED(status)); 

    } else {
        printf("can't create child process 0!");
    }
  
    return 0; 
} 
/*

*/