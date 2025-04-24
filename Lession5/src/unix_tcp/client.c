#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

// Khai bao duong dan Socket
#define SOCKET_PATH "/tmp/unix_socket_test"

#define LISTEN_BACKLOG 5
#define BUFF_SIZE 256

// Ham xu ly khi co loi
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)


void connect_server(int *mem_fd, struct sockaddr_un *serv_addr, int *status){
    /* Tạo socket */
    *mem_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (*mem_fd == -1){
        printf("Error: socket()\n");
        return;
    }

    *status = 1;
    if (connect(*mem_fd, (struct sockaddr *)serv_addr, sizeof(struct sockaddr_un)) == -1){
        printf("Error: connect()\n");
        *status = 0;
    }
}


int main(int argc, char *argv[])
{
    //Báo hệ điều hành: "Bỏ qua tín hiệu SIGPIPE" : tránh lỗi khi write() đến server ko tồn tại mà bị crack chương trình
    signal(SIGPIPE, SIG_IGN);

    int client_fd;
    int is_connect = 0;
    struct sockaddr_un serv_addr;
    char read_buffer[BUFF_SIZE];
	memset(&serv_addr, '0',sizeof(serv_addr));
	
    /* Khởi tạo địa chỉ server */
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, SOCKET_PATH);
	
    /* Kết nối tới server*/
    connect_server(&client_fd, &serv_addr, &is_connect);

    while (1)
    {
        if (is_connect == 0){
            printf("recconnect to server...\n");
            connect_server(&client_fd, &serv_addr, &is_connect);
            sleep(1);
            continue;
        }

        if (recv(client_fd, read_buffer, BUFF_SIZE, 0) < 0){
            printf("recv()\n");
            is_connect = 0;
            close(client_fd);
        }

        printf("Data from server: %s", read_buffer);

        if (send(client_fd, "Hello from client!\n", sizeof("Hello from client!\n"), 0) < 0){
            printf("send()\n");
            is_connect = 0;
            close(client_fd);
        }
    }

    close(client_fd);
    return 0;
}
