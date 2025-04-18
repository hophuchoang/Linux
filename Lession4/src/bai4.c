#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int arr[100];
pthread_t thread_count_even, thread_count_old;

static void *handler_count(void *args) 
{   
    int count = 0;
    int dk = 0;
    pthread_t tid = pthread_self();

    if (pthread_equal(tid, thread_count_old)) {
        dk = 1;
    }
    
    int len = sizeof(arr)/sizeof(arr[0]);
    for (int i = 0; i < len; i++) {
        if (arr[i]%2 == dk){
            count += arr[i];
        }
    }

    if (dk == 0){
        printf("Tong cac so chan la: %d\n", count);
    }else{
        printf("Tong cac so le la: %d\n", count);
    }
    
    pthread_exit(NULL); // exit
}

int main(int argc, char const *argv[])
{
    int len = sizeof(arr)/sizeof(arr[0]);
    for (int i = 0; i < len; i++){
        arr[i] = i+1;
    }

    /* code */
    int ret;

    if (ret = pthread_create(&thread_count_old, NULL, &handler_count, NULL)){
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }
    if (ret = pthread_create(&thread_count_even, NULL, &handler_count, NULL)){
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    pthread_join(thread_count_old,NULL); 
    pthread_join(thread_count_even,NULL); 
    

    return 0;
}