#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <signal.h>

void handler_signal_int(int num_sig){
    printf("SIGINT received.\n");
}

void handler_signal_term(int num_sig){
    exit(EXIT_SUCCESS);
}

int main() {

    if (signal(SIGINT, handler_signal_int) == SIG_ERR){
        fprintf(stderr, "Cannot handle SIGINT\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGTERM, handler_signal_term) == SIG_ERR){
        fprintf(stderr, "Cannot handle SIGTERM\n");
        exit(EXIT_FAILURE);
    }

    fd_set fds;
    struct timeval tv;
    char buf[100];

    while (1) {
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);

        printf("In: ");
        fflush(stdout);

        int ret = select(STDIN_FILENO + 1, &fds, NULL, NULL, NULL);

        if (ret > 0 && FD_ISSET(STDIN_FILENO, &fds)) {
            fgets(buf, sizeof(buf), stdin);
            printf("Out: %s", buf);
        }
    }

    return 0;
}
