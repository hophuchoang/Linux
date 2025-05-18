#ifndef UI_DISPLAY_H
#define UI_DISPLAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdarg.h>

#include "sock_defs.h" 

typedef enum {
    NORMAL = 0,
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
    WHITE = 37,
    ORANGE = 93
} ColorTerminal;

typedef enum {
    INF = 0,
    WAR = 1,
    ERR = 2
} TypeInfo;

void set_color(int colorCode);

void reset_color();

void show_help();

void show_init();

void show_close_app();

void show_my_ip(char* ip);

void show_my_port(int port);

void show_peer_disconnect(char *ip, int port);

void show_new_mess(char *ip, int port, char *mess);

void show_list_connect(socket_conn_t *conn, int len);

void show_info_connection(char *ip, int port);

void print_console(TypeInfo type, const char *format, ...);

#endif
