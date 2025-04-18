#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_t thread_id1, thread_id2;

static void *thr_handle(void *args) 
{
    pthread_t tid = pthread_self();

    if (pthread_equal(tid, thread_id1)) {
        printf("I'm thread_id1\n\n");
    } else {
        printf("I'm thread_id2\n");
    }

    pthread_exit(NULL);
}

static void *thr_handle2(void *args)
{
	printf("Hi im thread handle2\n");
}

int main(int argc, char const *argv[])
{
    /* code */
    int ret;

    if (ret = pthread_create(&thread_id1, NULL, &thr_handle, NULL)) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    sleep(2);

    if (ret = pthread_create(&thread_id2, NULL, &thr_handle, NULL)) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    sleep(2);

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    return 0;
}
