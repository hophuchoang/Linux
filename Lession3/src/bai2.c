#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2){
        printf("Chua truyen vao doi so nao! VD: ./example_program filename num-bytes [r/w] []\n");
        return 0;
    }

    if (strcmp(argv[1], "1") == 0){
        execlp("ls", "ls", "-l", "-a", "-h", NULL);

    } else if (strcmp(argv[1], "2") == 0){
        execlp("date", "date", NULL);
    }

    printf("Chuong trinh chinh khong the hien thi dong nay neu thuc hien cac lenh exec family!\n");

    return 0;
}
