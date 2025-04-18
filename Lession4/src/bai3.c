#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define THRESHOLD   10

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int counter = 0; // critical section <=> global resource

static void *handle_th1(void *args) 
{
    pthread_mutex_lock(&lock);
    sleep(counter);
    counter += 1;

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL); // exit or return;

}

int main(int argc, char const *argv[])
{
    /* code */
    int ret;

    while (counter < THRESHOLD)
    {
        pthread_t thread_procducer;

        if (ret = pthread_create(&thread_procducer, NULL, &handle_th1, NULL)) {
            printf("pthread_create() error number=%d\n", ret);
            return -1;
        }

        pthread_mutex_lock(&lock);
        pthread_cond_wait(&cond, &lock);
        printf("Global variable counter = %d.\n", counter);

        pthread_mutex_unlock(&lock);
    }

    pthread_mutex_unlock(&lock);

    return 0;
}