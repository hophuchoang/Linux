#include "ui_display.h"

void set_color(int colorCode) {
    printf("\033[0;%dm", colorCode);
}

void reset_color() {
    printf("\033[0m");
}

void show_help(){
    set_color(GREEN);
    printf("\nUse the commands bellow:\n");
    printf("1. help                             : display user interface options\n");
    printf("2. myip                             : display IP address of this app\n");
    printf("3. myport                           : display listening port of this app\n");
    printf("4. connect <destination> <port no>  : connect to the app of another computer\n");
    printf("5. list                             : list all the connection of this app\n");
    printf("6. terminate <connection id>        : terminate a connection\n");
    printf("7. send <connection id> <message>   : send a message to a connection\n");
    printf("8. exit:                            : close all connection & terminate this app\n");
    reset_color();
}

void show_init(){
    printf("--------------------------------- ");
    set_color(GREEN);
    printf("Chat Application");
    reset_color();
    printf(" ---------------------------------\n");

    show_help();

    printf("\n------------------------------------------------------------------------------------\n\n");
}

void show_my_ip(char* ip){
    printf("Server is listening at IP : ");
    set_color(BLUE);
    printf("%s\n", ip);
    reset_color();
}

void show_my_port(int port){
    printf("Server is listening at port : ");
    set_color(BLUE);
    printf("%d\n", port);
    reset_color();
}

void show_info_connection(char *ip, int port){
    set_color(BLUE);
    printf("\nHave new connection [ip: %s, port: %d]\n", ip, port);
    reset_color();
}

void show_peer_disconnect(char *ip, int port){
    set_color(BLUE);
    printf("\nDisconnect from peer [ip: %s, port: %d]\n", ip, port);
    reset_color();
}

void show_new_mess(char *ip, int port, char *mess){
    set_color(YELLOW);
    printf("\n[ip: %s, port: %d]$ %s\n", ip, port, mess);
    reset_color();
}

void print_console(TypeInfo type,  const char *format, ...) {
    va_list args;
    va_start(args, format);

    if (type == WAR) {set_color(ORANGE); printf("[WARNING] ");}
    else if (type == ERR) {set_color(RED); printf("[ERROR] ");}
    else {set_color(NORMAL); printf("[INFO] ");}

    vprintf(format, args);
    reset_color();

    va_end(args);
}

void show_list_connect(socket_conn_t *conn, int len){
    char header_ip_addr[] = "      IP Address       ";
    int total_width = strlen(header_ip_addr);

    printf("-------------------------------------\n");
    set_color(BLUE);
    printf("ID |%s|  Port No.\n", header_ip_addr);
    for (int i = 0; i < len; i++){
        if ((conn + i)->fd == -1)
            break;

        char ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(conn + i)->addr.sin_addr, ip, sizeof(ip));

        int ip_len = strlen(ip);
        int padding = (total_width - ip_len) / 2;

        printf("%d  |", i);
        for (int p = 0; p < padding; p++) printf(" ");
        printf("%s", ip);
        for (int t = 0; t < total_width - padding - ip_len; t++) printf(" ");
        printf("|  %d\n", ntohs((conn + i)->addr.sin_port));
    }
    reset_color();
    printf("-------------------------------------\n");
}

void show_close_app(int port){
    set_color(GREEN);
    printf("------------------- ");
    printf("Close program");
    printf(" -------------------\n");
    reset_color();
}