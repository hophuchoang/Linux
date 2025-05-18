#include "app_func.h"

void check_param_cmd(char *str, char *key_param, char *param_1, char *param_2){
    int len = strlen(str);
    int start = 0;
    int index = 0;

    for (int i = 0; i < len; i++){
        if (str[i] == '\n'){
            break;
        }

        if (str[i] == ' ' && strlen(key_param) > 0 && start < 2){
            start += 1;
            index = 0;
        }
        else
        {
            if (start == 0){
                key_param[index++] = str[i];

            }else if (start == 1){
                param_1[index++] = str[i];

            }else if (start == 2){
                param_2[index++] = str[i];
            }
        }
    }
}

int is_number(const char *str) {
    if (str[0] == '\0') return 0;

    while (*str) {
        if (!isdigit(*str))
            return 0;
        str++;
    }
    return 1;
}

int disconnect_peer_by_fd(int fd, socket_conn_t *list_connection, fd_set *fd_set, socket_conn_t *peer_delete){
    int assign_next = 0;
    if (fd < 0) return 0;

    for (int i = 0; i < MAX_CONNECTION; i++){
        int _fd = list_connection[i].fd;
        if (_fd < 0) break;
        
        if (_fd == fd || assign_next == 1){
            if (i < MAX_CONNECTION - 1 && list_connection[i+1].fd > 0){
                if (assign_next == 0) *peer_delete = list_connection[i];

                list_connection[i] = list_connection[i+1];
                assign_next = 1;

            }else{
                list_connection[i].fd = -1;
                FD_CLR(fd, fd_set);
                close(fd);
                return 1;
            }
        }
    }

    return 0;
}

int disconnect_peer_by_index(int index, socket_conn_t *list_connection, fd_set *fd_set, socket_conn_t *peer_delete){
    if (index < 0 || index >= MAX_CONNECTION) return 0;
    int fd = list_connection[index].fd;
    return disconnect_peer_by_fd(fd, list_connection, fd_set, peer_delete);
}

int send_message(int index, const socket_conn_t *list_connection, const char* mess){
    if (index < 0 || index >= MAX_CONNECTION) return 0;
    int fd = list_connection[index].fd;
    if (fd < 0) return 0;
    write(fd, mess, MAX_LEN_MESS);
    return 1;
}

int close_all_connection(const socket_conn_t *list_connection){
    for (int i = 0; i < MAX_CONNECTION; i++){
        int fd = list_connection[i].fd;
        if (fd < 0) break;
        close(fd);
    }
    return 1;
}