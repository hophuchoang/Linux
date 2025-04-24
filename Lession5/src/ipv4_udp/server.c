#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>     //  Chứa cấu trúc cần thiết cho socket. 
#include <netinet/in.h>     //  Thư viện chứa các hằng số, cấu trúc khi sử dụng địa chỉ trên internet
#include <arpa/inet.h>
#include <unistd.h>

#define LISTEN_BACKLOG 5
#define BUFF_SIZE 1024
#define PORT 8080

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)


int main(int argc, char *argv[])
{
    int port_no, len, opt;
    int server_fd, new_socket_fd;
    char buffer_recieve[BUFF_SIZE];
    int data_recieve = 0;
    struct sockaddr_in serv_addr, client_addr;

    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    
    /* Tạo socket */
    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd == -1)
        handle_error("socket()");
    // fprintf(stderr, "ERROR on socket() : %s\n", strerror(errno));

    /* Khởi tạo địa chỉ cho server */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr =  INADDR_ANY; //inet_addr("192.168.5.128"); //INADDR_ANY

    /* Gắn socket với địa chỉ server */
    if (bind(server_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){        
        handle_error("bind()");
        close(server_fd);
    }

    /* Dùng để lấy thông tin client */
	len = sizeof(client_addr);

    printf("Server udp is listening at ip: %s, port : %d \n....\n", inet_ntoa(serv_addr.sin_addr), PORT);

    while (1) {
        // printf("Sockaddr_in info:\n");
        // printf("  IP Address : %s\n", inet_ntoa(client_addr.sin_addr));
        // printf("  Port       : %d\n", ntohs(client_addr.sin_port));

        int recv_len = recvfrom(server_fd, &data_recieve, sizeof(data_recieve), 0, (struct sockaddr*)&client_addr, &len);
        if (recv_len < 0) {
            perror("recvfrom failed");
            break;
        }

        printf("Sockaddr_in info:\n");
        printf("  IP Address : %s\n", inet_ntoa(client_addr.sin_addr));
        printf("  Port       : %d\n", ntohs(client_addr.sin_port));

        printf("Nhận từ client: %d\n", data_recieve);
        data_recieve += 1;

        int send_len = sendto(server_fd, &data_recieve, sizeof(data_recieve), 0, (struct sockaddr*)&client_addr, len);
        if (send_len < 0) {
            perror("sendto failed");
            break;
        }

    }
    close(server_fd);
    return 0;
}