#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

// Khai bao duong dan Socket
#define SOCKET_PATH "/tmp/unix_dgram_socket"

#define LISTEN_BACKLOG 5
#define BUFF_SIZE 256

// Ham xu ly khi co loi
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[])
{
    int port_no, len, opt;
    int server_fd, new_socket_fd;
    char buffer_recieve[BUFF_SIZE];
    int data_recieve = 0;
    struct sockaddr_un serv_addr, client_addr;

    memset(&serv_addr, 0, sizeof(struct sockaddr_un));
    memset(&client_addr, 0, sizeof(struct sockaddr_un));
    
    /* Tạo socket */
    server_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (server_fd == -1)
        handle_error("socket()");
    // fprintf(stderr, "ERROR on socket() : %s\n", strerror(errno));

    // Xóa socket file nếu đã tồn tại
    unlink(SOCKET_PATH);

    /* Khởi tạo địa chỉ cho server */
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, SOCKET_PATH);

    /* Gắn socket với địa chỉ server */
    if (bind(server_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){        
        handle_error("bind()");
        close(server_fd);
    }

    /* Dùng để lấy thông tin client */
	len = sizeof(client_addr);

    printf("Server UNIX UDP is listening at path: %s\n", SOCKET_PATH);

    while (1) {
        int recv_len = recvfrom(server_fd, &data_recieve, sizeof(data_recieve), 0, (struct sockaddr*)&client_addr, &len);
        if (recv_len < 0) {
            perror("recvfrom failed");
            break;
        }

        printf("Client path info: %s\n", client_addr.sun_path);
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