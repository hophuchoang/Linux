#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define THRESHOLD   1000000
#define NUMBER_THREAD 4

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int sum = 0; // critical section <=> global 
int sum1, sum2, sum3, sum4;
int arr[THRESHOLD];
int count_thread = 0;

int sum_n[4];

typedef struct {
    int value;
    char padding[60]; // Đảm bảo struct chiếm 64 bytes (cache line)
} PaddedSum;

PaddedSum sums[NUMBER_THREAD]; // 4 phần tử tương ứng 4 thread

static void *handler_th(void *args) 
{   
    pthread_mutex_lock(&lock);
    // printf("%ld, %d\n", *start*(THRESHOLD/4), (*start+1)*(THRESHOLD/4));

    for (int i = count_thread*(THRESHOLD/4); i < (count_thread + 1)*(THRESHOLD/4); i++){
        sum += arr[i];
    }

    count_thread += 1;
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL); // exit
}


static void *handler_th_sum1(void *args) 
{   
    // printf("%ld, %d\n", *start*(THRESHOLD/4), (*start+1)*(THRESHOLD/4));

    for (int i = 0; i < 250000; i++){
        sums[0].value += arr[i];
    }

    pthread_exit(NULL); // exit
}


static void *handler_th_sum2(void *args) 
{   
    // printf("%ld, %d\n", *start*(THRESHOLD/4), (*start+1)*(THRESHOLD/4));

    for (int i = 250000; i < 500000; i++){
        sums[1].value += arr[i];
    }

    pthread_exit(NULL); // exit
}


static void *handler_th_sum3(void *args) 
{   
    // printf("%ld, %d\n", *start*(THRESHOLD/4), (*start+1)*(THRESHOLD/4));

    for (int i = 500000; i < 750000; i++){
        sums[2].value += arr[i];
    }

    pthread_exit(NULL); // exit
}


static void *handler_th_sum4(void *args) 
{   
    // printf("%ld, %d\n", *start*(THRESHOLD/4), (*start+1)*(THRESHOLD/4));

    for (int i = 750000; i < 1000000; i++){
        sums[3].value += arr[i];
    }

    pthread_exit(NULL); // exit
}


int main(int argc, char const *argv[])
{
    printf("Bắt đầu chương trình...\n");
    // clock_t time = clock();

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    /* code */
    int ret;
    pthread_t thread[NUMBER_THREAD];

    arr[0] = 1;
    arr[249999] = 2;
    arr[250000] = 2;
    arr[500000] = 3;
    arr[750000] = 4;

    int c = 1;

    if (c == 0){
        for (int i = 0; i < 1000000; i++){
            sum += arr[i];
        }

    }else if (c == 1){

        if (ret = pthread_create(&thread[0], NULL, &handler_th_sum1, NULL)){
            printf("pthread_create() error number=%d\n", ret);
        }

        if (ret = pthread_create(&thread[1], NULL, &handler_th_sum2, NULL)){
            printf("pthread_create() error number=%d\n", ret);
        }

        if (ret = pthread_create(&thread[2], NULL, &handler_th_sum3, NULL)){
            printf("pthread_create() error number=%d\n", ret);
        }

        if (ret = pthread_create(&thread[3], NULL, &handler_th_sum4, NULL)){
            printf("pthread_create() error number=%d\n", ret);
        }

    }else{

        for (int i = 0; i < NUMBER_THREAD; i++){
            if (ret = pthread_create(&thread[i], NULL, &handler_th, NULL)){
                printf("pthread_create() error number=%d\n", ret);
            }
        }
    }

    // used to block for the end of a thread and release
    
    if (c != 0){
        for (int i = 0; i < NUMBER_THREAD; i++){
            pthread_join(thread[i], NULL);
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    long duration = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
    printf("Thời gian thực thi = %ld ns\n", duration);

    if (c == 1){
        for (int i = 0; i < NUMBER_THREAD; i++) {
            sum += sums[i].value;
        }
        // sum = sum_n[0] + sum_n[1] + sum_n[2] + sum_n[3];
    }

    printf("Global variable sum = %d\n", sum);

    // clock_t delta_time = clock() - time;

    // printf("Thời gian thực thi = %ld\n", delta_time);

    return 0;
}

/*
only main:               2959976ns
                         1550960ns
4 thread chạy 4 sum :   10444051ns
4 thread chạy 1 sum:     4225659ns
*/