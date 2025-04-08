#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <setjmp.h>
#include <unistd.h> 
#include <fcntl.h> 

jmp_buf jumpBuffer;

int main(int argc, char *argv[]) {
    char folder_file[100] = "data/"; 
    int num_bytes;
    int fd;

    if (argc < 2){
        printf("Chua truyen vao doi so nao! VD: ./example_program filename num-bytes [r/w] []\n");
        return 0;
    }

    if (strlen(argv[1]) == 0){
        printf("Ten file khong duoc rong!\n");
        return 0;
    }

    // Mo file de kiem tra file co ton tai hay khong
    fd = open(strcat(folder_file, argv[1]), O_RDWR);         
    if (-1 == fd) { 
	    printf("Loi khi mo file [%s], file khong hop le!\n", folder_file);
        return 0;
    }

    if (argc < 3){
        printf("num-bytes rong\n");
        close(fd);
        return 0;
    }

    if (setjmp(jumpBuffer) != 0){
        printf("num-bytes = %s, khong phai la so!\n", argv[2]);
        close(fd);
        return 0;

    }else{
        if (!atoi(argv[2])){
            longjmp(jumpBuffer, 1);
        }
        num_bytes = atoi(argv[2]);
    }

    if (argc < 4){
        printf("Tham so doc/ghi chua duoc truyen vao [r/w]\n");
        close(fd);
        return 0;
    }

    if (strlen(argv[3]) != 1 || (argv[3][0] != 'r' && argv[3][0] != 'w')){
        printf("tham so doc va ghi khong hop le [%s], chi dung [r,w]\n", argv[3]);
        close(fd);
        return 0;
    }

    if (argv[3][0] == 'r'){
        char buffer[2048];
        ssize_t bytesRead = read(fd, buffer, num_bytes); 
        if (bytesRead < 0){
            printf("Loi khi doc file!");

        }else{
            buffer[bytesRead] = '\0';
            printf("Noi dung file:\n%s\n", buffer);
        }

        close(fd);
        return 0;
    }

    if (argv[3][0] == 'w'){
        if (argc < 5){
            printf("Khong co noi dung gi duoc gi vao!\n");
            close(fd);
            return 0;
        }

        int len_str_write = strlen(argv[4]);
        if (len_str_write > 0){
            if (num_bytes > len_str_write){
                num_bytes = len_str_write;
            }

            int numb_write = write(fd, argv[4], num_bytes);
            printf("Write %d bytes to %s\n", numb_write, folder_file);
        }

        close(fd);
    }

    return 0;
}
