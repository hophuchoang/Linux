#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void handler_signal_tspt(int num){
    printf("SIGTSTP ignored\n");
}

int main(int argc, char *argv[]){
    printf("Process pid: %d\n", getpid());

    if (signal(SIGTSTP, handler_signal_tspt) == SIG_ERR){
        fprintf(stderr, "Cannot handle SIGTSTP\n");
        exit(EXIT_FAILURE);
    }

    while (1);
}

/*
    nếu không xử lý tín hiệu SIGTSTP và người dùng nhấn Ctrl+Z thì chương trình sẽ bị tạm dừng và quay trở lại dòng lệnh
*/