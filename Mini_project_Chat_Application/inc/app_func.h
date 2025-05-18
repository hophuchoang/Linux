#ifndef APP_FUNC_H
#define APP_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "app_define.h"
#include "sock_defs.h"

void check_param_cmd(char *str, char *key_param, char *param_1, char *param_2);

int is_number(const char *str);

int disconnect_peer_by_fd(int fd, socket_conn_t *list_connection, fd_set *fd_set, socket_conn_t *peer_delete);

int disconnect_peer_by_index(int index, socket_conn_t *list_connection, fd_set *fd_set, socket_conn_t *peer_delete);

int send_message(int index, const socket_conn_t *list_connection, const char* mess);

int close_all_connection(const socket_conn_t *list_connection);


#endif