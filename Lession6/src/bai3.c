#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>


int count_signal_usr1 = 0;

void handler_signal_usr1(int signum){
    count_signal_usr1 += 1;
    printf("Received signal from parent %d time\n", count_signal_usr1);
    if (count_signal_usr1 == 5){
        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char *argv[]){
    pid_t child_pid;
    child_pid = fork();

    if (child_pid == 0){ // Process con
        // printf("\nIm the child process\n");
        // printf("My PID is: %d, my parent PID is: %d\n", getpid(), getppid());

        if (signal(SIGUSR1, handler_signal_usr1) == SIG_ERR){
            fprintf(stderr, "Cannot handle SIGUSR1\n");
            exit(EXIT_FAILURE);
        }

        while (1);

    } else if (child_pid > 0){
        // printf("\nIm the parent process\n");
        // printf("My PID is: %d, my parent PID is: %d, my child PID is: %d\n", getpid(), getppid(), child_pid);

        // Thời gian chờ để các process con được khởi tạo
        sleep(0.1);

        int status;
        clock_t time = -2.0*CLOCKS_PER_SEC;

        while (1){
            pid_t result = waitpid(child_pid, &status, WNOHANG);

            if (result == 0){
                clock_t now = clock();
                double duration = (double)(now - time) / CLOCKS_PER_SEC;

                if (duration > 2.0){
                    time = now;
                    kill(child_pid, SIGUSR1);
                }

            }else if (result == child_pid){
                break;
            }
        }

    } else {
        printf("can't create child process!");
    }

    return 0;
}

/*
    Hàm kill thực hiện gửi tín hiệu giữa các tiến trình
*/