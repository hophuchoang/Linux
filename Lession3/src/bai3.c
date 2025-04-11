#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void handle_sigusr1(int signum) {
    printf(">> Child received SIGUSR1! (signal number: %d)\n", signum);
}
  
int main (void) 
{ 
    pid_t child_pid;
    child_pid = fork();

    if (child_pid == 0){ // Process con
        signal(SIGUSR1, handle_sigusr1);
        while(1){
            // pause();
        }

        exit(0);

    } else if (child_pid > 0){
        sleep(2);

        int status;
        while (1)
        {
            pid_t result = waitpid(child_pid, &status, WNOHANG);

            if (result == 0){ // tien trinh con chua ket thuc
                kill(child_pid, SIGUSR1);  // Gửi tín hiệu đến con
                sleep(1);

            } else if (result == child_pid){
                printf("Process child finished!\n");

                break;
            }
        }

    } else {
        printf("can't create child process!");
    }
  
    return 0; 
} 