#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_rwlock_t rwlock;
int shared_data = 0;

static void* handle_reader(void* arg) {
    pthread_rwlock_rdlock(&rwlock); // Lock chế độ đọc
    printf("read shared_data = %d\n", shared_data);
    pthread_rwlock_unlock(&rwlock); // Unlock sau khi đọc
    return NULL;
}

static void* handle_writer(void* arg) {
    pthread_rwlock_wrlock(&rwlock); // Lock chế độ ghi
    shared_data += 1;
    printf("Writer shared_data to %d\n", shared_data);
    pthread_rwlock_unlock(&rwlock); // Unlock sau khi ghi
    return NULL;
}

int main(int argc, char const *argv[]) {

    pthread_rwlock_init(&rwlock, NULL); // Khởi tạo rwlock

    pthread_t thread_read[5];
    pthread_t thread_write[2];

    int ret;

    int lenRead = sizeof(thread_read)/sizeof(pthread_t);
    int lenWrite = sizeof(thread_write)/sizeof(pthread_t);

    for (int i = 0; i < lenRead; i++){
        if (ret = pthread_create(&thread_read[i], NULL, &handle_reader, NULL)){
            printf("pthread_create() error number=%d\n", ret);
            return -1;
        }
    }

    for (int i = 0; i < lenWrite; i++){
        if (ret = pthread_create(&thread_write[i], NULL, &handle_writer, NULL)){
            printf("pthread_create() error number=%d\n", ret);
            return -1;
        }
    }

    for (int i = 0; i < lenRead; i++){
        pthread_join(thread_read[i], NULL);
    }

    for (int i = 0; i < lenWrite; i++){
        pthread_join(thread_write[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock); // Giải phóng rwlock

    printf("Data = %d when all thread finish!\n", shared_data);

    return 0;
}
