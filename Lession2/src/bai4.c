#include <stdio.h>
#include <fcntl.h>      // open(), O_WRONLY...
#include <unistd.h>     // write(), close()
#include <sys/stat.h>   // struct stat
#include <string.h>     // strlen
#include <time.h>       // ctime()

int main(int argc, char *argv[]) {
    const char * filename = "data/text_4.txt";
    const char * data_write = "data bai 4\n";
    int num_bytes;
    int fd;

    // Mo file de kiem tra file co ton tai hay khong
    fd = open(filename, O_RDWR | O_CREAT, 0666);         
    if (-1 == fd) { 
	    printf("Loi khi mo file\n");
        return 0;
    }

    int numb_write = write(fd, data_write, strlen(data_write));
    close(fd);

    struct stat file_stat;
    if (stat(filename, &file_stat) == -1){
        printf("Loi khi lay thong tin file\n");
        return 0;
    }

    printf("Ten file: %s\n", filename);
    printf("Loai file: ");
    if (S_ISREG(file_stat.st_mode)){
        printf("file thuong\n");
    }else if (S_ISDIR(file_stat.st_mode)){
        printf("thu muc\n");
    }else{
        printf("file khac\n");
    }

    printf("Thoi gian chinh sua lan cuoi: %s", ctime(&file_stat.st_mtime));
    printf("Kich thuoc file: %ld bytes\n", file_stat.st_size);

    return 0;
}
