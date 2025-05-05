#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int count_signal_alrm = 0;

void handler_signal_alrm(int num){
    count_signal_alrm += 1;
    printf("Timer: %d seconds\n", count_signal_alrm);
    if (count_signal_alrm == 10){
        exit(EXIT_SUCCESS);
    }

    alarm(1);
}

int main(int argc, char *argv[]){
    printf("Process pid: %d\n", getpid());

    if (signal(SIGALRM, handler_signal_alrm) == SIG_ERR){
        fprintf(stderr, "Cannot handle SIGNINT\n");
        exit(EXIT_FAILURE);
    }

    alarm(1);

    while (1){
        // alarm(1);
        // pause();
    }
}

/*
    Nếu không gọi lại alarm(1) trong hàm xử lý thì chương trình sẽ không được gọi lại 
*/