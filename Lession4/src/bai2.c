#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define THRESHOLD   1000000
#define NUMBER_THREAD 3

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int counter = 0; // critical section <=> global resource

static void *handler_th(void *args) 
{   
    pthread_mutex_lock(&lock);
    for (int i = 0; i < THRESHOLD; i++){
        counter += 1;
    }

    pthread_mutex_unlock(&lock);
    
    pthread_exit(NULL); // exit
}

int main(int argc, char const *argv[])
{
    /* code */
    int ret;
    pthread_t thread[NUMBER_THREAD];

    for (int i = 0; i < NUMBER_THREAD; i++){
        if (ret = pthread_create(thread+i, NULL, &handler_th, NULL)){
            printf("pthread_create() error number=%d\n", ret);
        }
    }
    
    // used to block for the end of a thread and release
    for (int i = 0; i < NUMBER_THREAD; i++){
        pthread_join(thread[i], NULL);
    }

    printf("Global variable counter = %d\n", counter);

    return 0;
}