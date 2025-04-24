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

int main(int argc, char *argv[]){
    signal(SIGPIPE, SIG_IGN);

    int server_fd, new_socket_fd;
    char buffer_recieve[BUFF_SIZE];
    struct sockaddr_un serv_addr;

    memset(&serv_addr, 0, sizeof(struct sockaddr_un));

    // Tạo socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1) {
        handle_error("socket()");
    }

    // Xóa socket file nếu đã tồn tại
    unlink(SOCKET_PATH);

    /* Khởi tạo địa chỉ cho server */
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, SOCKET_PATH);

    /* Gắn socket với địa chỉ server */
    if (bind(server_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        handle_error("bind()");

    /* Nghe tối đa 5 kết nối trong hàng đợi */
    if (listen(server_fd, LISTEN_BACKLOG) == -1)
        handle_error("listen()");

    printf("Server UNIX TCP is listening at socket path: %s\n", SOCKET_PATH);

    new_socket_fd = accept(server_fd, NULL, NULL);
    if (new_socket_fd == -1) {
        perror("accept");
        handle_error("accept()");
    }
    system("clear");
    printf("Server : got connection \n");

    // Chấp nhận kết nối
    while (1) {
        write(new_socket_fd, "Hello from server\n", sizeof("Hello from server\n"));

        read(new_socket_fd, buffer_recieve, BUFF_SIZE);
        printf("Data from Client: %s", buffer_recieve);

        sleep(1);
    }

    close(new_socket_fd);
    close(server_fd);
    unlink(SOCKET_PATH);
    return 0;
}






