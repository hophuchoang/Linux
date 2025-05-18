#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/select.h>
#include <signal.h>
#include <ctype.h>

#include "socket.h"
#include "ui_display.h"
#include "app_func.h"

int exit_by_signal = 0;
  
int main(int argc, char *argv[]) 
{
    char ip_server[INET_ADDRSTRLEN];
    int port_server;

    socket_conn_t serv_socket, list_connection[MAX_CONNECTION];
    fd_set master_fds, read_fds;
    int max_fd;
    char buf_read[100];

    #ifdef SERVER_IP
        strcpy(ip_server, SERVER_IP);
    #else
        ip_server = "0.0.0.0";
    #endif

    for (int i = 0; i < MAX_CONNECTION; i++) list_connection[i].fd = -1;

    if (argc < 2){
        print_console(ERR, "Missing port parameter for connection\n");
        print_console(ERR, "Use: $.<name_app> <port>\n");
        exit(1);
    }

    if (is_number(argv[1]) == 0){
        print_console(ERR, "port %s is not number!\n", argv[1]);
        return 0;
    }
    port_server = atoi(argv[1]);

    show_init();

    int temp = create_server(&serv_socket, ip_server, port_server);
    if (temp > 0){
        show_my_port(port_server);
    }

    FD_ZERO(&master_fds);
    FD_SET(serv_socket.fd, &master_fds);
    max_fd = serv_socket.fd;

    while (1)
    {
        read_fds = master_fds;
        FD_SET(STDIN_FILENO, &read_fds);

        printf("\nInput cmd: ");
        fflush(stdout);

        int ret = select(max_fd + 1, &read_fds, NULL, NULL, NULL);
        if (ret < 0 && errno != EINTR) {
            print_console(ERR, "select\n");
            break;
        }

        if (FD_ISSET(serv_socket.fd, &read_fds)) {
            socket_conn_t peer;
            int add_new_peer = 0;

            if(check_new_peer(serv_socket.fd, &peer) > 0){
                char ip[INET_ADDRSTRLEN];
                int port;
                get_ip(&peer, ip);
                show_info_connection(ip, get_port(&peer));
            }

            for (int i = 0; i < MAX_CONNECTION; i++) {
                if (list_connection[i].fd < 0) {
                    list_connection[i] = peer;
                    add_new_peer = 1;
                    break;
                }
            }

            if (add_new_peer == 1){
                FD_SET(peer.fd, &master_fds);
                if (peer.fd > max_fd) max_fd = peer.fd;

            }else{
                print_console(WAR, "Cannot add new connection because the number is over limit!");
            }
        }

        for (int i = 0; i < MAX_CONNECTION; i++){
            int fd = list_connection[i].fd;
            
            if (fd > 0){
                if (FD_ISSET(fd, &read_fds)) {
                    char read_buffer[MAX_LEN_MESS] = {0};
                    int bytes = read(fd, read_buffer, MAX_LEN_MESS);

                    if (bytes <= 0){
                        socket_conn_t peer_delete;
                        char ip[INET_ADDRSTRLEN];
                        
                        if (disconnect_peer_by_fd(fd, list_connection, &master_fds, &peer_delete) > 0){
                            get_ip(&peer_delete, ip);
                            show_peer_disconnect(ip, get_port(&peer_delete));
                        }

                    }else{
                        char ip[INET_ADDRSTRLEN];
                        get_ip(&list_connection[i], ip);
                        show_new_mess(ip, get_port(&list_connection[i]), read_buffer);
                    }
                    
                }
            }
        }

        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            char key_param[20] = {0};
            char param1[20] = {0};
            char param2[100] = {0};

            fgets(buf_read, sizeof(buf_read), stdin);
            check_param_cmd(buf_read, key_param, param1, param2);

            if (strcmp(key_param, "help") == 0){
                show_help();

            }else if(strcmp(key_param, "myip") == 0){
                char ip[INET_ADDRSTRLEN];
                get_ip(&serv_socket, ip);
                show_my_ip(ip);

            }else if (strcmp(key_param, "myport") == 0){
                show_my_port(get_port(&serv_socket));

            }else if (strcmp(key_param, "list") == 0){
                show_list_connect(list_connection, MAX_CONNECTION);

            }else if (strcmp(key_param, "exit") == 0){
                break;

            }else if (strcmp(key_param, "connect") == 0){
                socket_conn_t peer;

                if (is_number(param2) == 0){
                    print_console(ERR, "port %s is not number!\n", param2);
                    continue;
                }

                if (strcmp(param1, ip_server) == 0 &&  port_server == atoi(param2)){
                    print_console(WAR, "Can't create peer, [ip: %s, port: %d] match server\n", param1, atoi(param2));
                    continue;
                }

                if (create_peer_client(&peer, param1, atoi(param2)) == 0){
                    print_console(ERR, "create socket client fail!\n");
                    continue;
                }

                print_console(INF, "Create socket completed\n");

                // // Thêm vào danh sách client
                for (int i = 0; i < MAX_CONNECTION; i++) {
                    if (list_connection[i].fd < 0) {
                        list_connection[i] = peer;
                        break;
                    }
                }

                FD_SET(peer.fd, &master_fds);
                if (peer.fd > max_fd) max_fd = peer.fd;

            }else if (strcmp(key_param, "terminate") == 0){
                socket_conn_t peer_delete;

                if (is_number(param1) == 0){
                    print_console(ERR, "index %s is not number!\n", param1);
                    continue;
                }

                if (disconnect_peer_by_index(atoi(param1), list_connection, &master_fds, &peer_delete) == 0){
                    print_console(ERR, "disconnect peer fail!\n");
                    continue;
                }

                print_console(INF, "disconnect peer index = %s completed!\n", param1);
            
            }else if (strcmp(key_param, "send") == 0){
                if (is_number(param1) == 0){
                    print_console(ERR, "index %s is not number!\n", param1);
                    continue;
                }

                if (strlen(param2) == 0){
                    print_console(ERR, "len of mess = 0\n");
                    continue;
                }

                if (send_message(atoi(param1), list_connection, param2) == 0){
                    print_console(ERR, "send mess fail!\n");
                    continue;
                }

                print_console(INF, "send message completed!\n");

            }else{
                print_console(WAR, "Command does not exist: %s", buf_read);
            }
        }
    }
    
    close_all_connection(list_connection);
    close(serv_socket.fd);
    show_close_app();

    return 0; 
} 