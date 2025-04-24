#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

// Khai bao duong dan Socket
#define SERVER_SOCKET_PATH "/tmp/unix_dgram_socket"
#define CLIENT_SOCKET_PATH "/tmp/unix_dgram_client"

#define BUFF_SIZE 256

// Ham xu ly khi co loi
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[])
{
    int portno, len;
    int client_fd;
    struct sockaddr_un serv_addr, client_addr;
    char read_buffer[BUFF_SIZE];

	memset(&serv_addr, 0, sizeof(serv_addr));
    memset(&client_addr, 0, sizeof(client_addr));
	
    /* Tạo socket UDP */
    client_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (client_fd == -1)
        handle_error("socket()");

    // Xóa socket client cũ nếu có
    unlink(CLIENT_SOCKET_PATH);

    // Bind socket client vào file riêng
    memset(&client_addr, 0, sizeof(struct sockaddr_un));
    client_addr.sun_family = AF_UNIX;
    strcpy(client_addr.sun_path, CLIENT_SOCKET_PATH);

    // Gắn socket với địa chỉ client
    if (bind(client_fd, (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1) {
        handle_error("bind client");
    }

    // Thiết lập địa chỉ server
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, SERVER_SOCKET_PATH);

    len = sizeof(serv_addr);
    int data_send = 0;

    printf("Client UNIX UDP is communicate at path: %s\n", SERVER_SOCKET_PATH);

    while (1)
    {
        int send_len = sendto(client_fd, &data_send, sizeof(data_send), 0, (struct sockaddr*)&serv_addr, len);
        if (send_len < 0) {
            perror("sendto failed");
            break;
        }

        int recv_len = recvfrom(client_fd, &data_send, sizeof(data_send), 0, (struct sockaddr*)&serv_addr, &len);
        if (recv_len < 0) {
            perror("recvfrom failed");
            break;
        }

        printf("Nhận từ server: %d\n", data_send);
        data_send += 1;

        sleep(1);
    }
    
    close(client_fd);
    return 0;
}
