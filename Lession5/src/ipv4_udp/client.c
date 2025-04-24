#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>     //  Chứa cấu trúc cần thiết cho socket. 
#include <netinet/in.h>     //  Thư viện chứa các hằng số, cấu trúc khi sử dụng địa chỉ trên internet
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 8080

#define BUFF_SIZE 256
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[])
{
    int portno, len;
    int server_fd;
    struct sockaddr_in serv_addr;
    char read_buffer[100];
	memset(&serv_addr, 0, sizeof(serv_addr));
	
    /* Tạo socket UDP */
    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd == -1)
        handle_error("socket()");

    /* Khởi tạo địa chỉ server */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port   = htons(SERVER_PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    len = sizeof(serv_addr);
    int data_send = 0;

    printf("Client udp is communicate at ip: %s, port : %d \n....\n", inet_ntoa(serv_addr.sin_addr), SERVER_PORT);

    while (1)
    {
        // printf("Sockaddr_in info:\n");
        // printf("  IP Address : %s\n", inet_ntoa(serv_addr.sin_addr));
        // printf("  Port       : %d\n", ntohs(serv_addr.sin_port));

        int send_len = sendto(server_fd, &data_send, sizeof(data_send), 0, (struct sockaddr*)&serv_addr, len);
        if (send_len < 0) {
            perror("sendto failed");
            break;
        }

        printf("Sockaddr_in info:\n");
        printf("  IP Address : %s\n", inet_ntoa(serv_addr.sin_addr));
        printf("  Port       : %d\n", ntohs(serv_addr.sin_port));

        int recv_len = recvfrom(server_fd, &data_send, sizeof(data_send), 0, (struct sockaddr*)&serv_addr, &len);
        if (recv_len < 0) {
            perror("recvfrom failed");
            break;
        }

        printf("Nhận từ server: %d\n", data_send);
        data_send += 1;

        sleep(1);
    }
    

    return 0;
}
