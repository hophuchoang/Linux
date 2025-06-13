#include <stdio.h>
#include <fcntl.h>      // open(), O_WRONLY...
#include <unistd.h>     // write(), close()
#include <sys/stat.h>   // struct stat
#include <string.h>     // strlen

int main(int argc, char *argv[]) {
    int fd;

    if (argc < 2 || strlen(argv[1]) == 0){
        return 0;
    }

    // if (chmod(argv[1], 0777) != 0) {
    //     perror("Cannot change permission!!!\n");
    //     return 0;
    // }

    fd = open(argv[1], O_RDWR);         
    if (-1 == fd) { 
	    printf("Cannot open file!, need run with sudo <app_name>\n");
        return 0;
    }

    int numb_write = write(fd, argv[2], strlen(argv[2]));

    close(fd);

    return 0;
}
