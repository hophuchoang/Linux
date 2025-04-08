// C program to illustrate 
// I/O system Calls 
#include<stdio.h> 
#include<string.h> 
#include<unistd.h> 
#include<fcntl.h> 
  
int main (void) 
{ 
    char str1[] = "Hello\n";
    char str2[] = "HE";

    int fd; 
    int numb_read, numb_write, numb_write2;
  
    // assume foobar.txt is already created 
    fd = open("data/text.txt", O_RDWR);         
    if (-1 == fd) { 
	    printf("open() text.txt failed\n");
    }      

    numb_write = write(fd, str1, strlen(str1));
    printf("Write %ld bytes to text.txt\n", strlen(str1));
  
    long pos = lseek(fd, 0, SEEK_SET);
    printf("File pointer is at position: %ld\n", pos);

    numb_write2 = write(fd, str2, strlen(str2));
    printf("Write %ld bytes to hello.txt\n", strlen(str2));

    close(fd); 
  
    return 0; 
} 