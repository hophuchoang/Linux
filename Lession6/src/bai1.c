#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int count_signal_int = 0;

void handler_signal_int(int num){
    count_signal_int += 1;
    printf("Recieved signal_int %d time\n", count_signal_int);
    if (count_signal_int == 3){
        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char *argv[]){
    printf("Process pid: %d\n", getpid());
    if (signal(SIGINT, handler_signal_int) == SIG_ERR){
        fprintf(stderr, "Cannot handle SIGNINT\n");
        exit(EXIT_FAILURE);
    }

    while (1);
}

/*
Nếu như bỏ qua tín hiệu SIGINT thì chương trình sẽ ko kết thúc khi nhấn Ctrl+C hoặc nhận tín hiệu SIGNINT từ tiến trình khác 
*/