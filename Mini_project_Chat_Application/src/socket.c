#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "sock_defs.h"


void get_ip(const socket_conn_t *peer, char *ip){
    inet_ntop(AF_INET, &(peer->addr).sin_addr, ip, INET_ADDRSTRLEN);
}

int get_port(socket_conn_t *peer){
    return ntohs((peer->addr).sin_port);
}

int create_server(socket_conn_t* _soc, char *ip, int port){
    _soc->type_sock = 1;
    memset(&(_soc->addr), 0, sizeof(struct sockaddr_in));
    
    /* Tạo socket */
    _soc->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_soc->fd == -1)
        handle_error("socket()");

    (_soc->addr).sin_family = AF_INET;
    (_soc->addr).sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &(_soc->addr).sin_addr.s_addr) <= 0) {
        handle_error("Invalid IP address");
        return 1;
    }
    // (_soc->addr).sin_addr.s_addr =  INADDR_ANY;

    if (bind(_soc->fd, (struct sockaddr*)&(_soc->addr), sizeof(struct sockaddr_in)) == -1)
        handle_error("bind()");

    if (listen(_soc->fd, LISTEN_BACKLOG) == -1)
        handle_error("listen()");
    
    return 1;
}

int check_new_peer (int fd, socket_conn_t* _soc_client){
    int len = sizeof(_soc_client->addr);

    _soc_client->fd  = accept(fd, (struct sockaddr*)&(_soc_client->addr), (socklen_t *)&len); 
    if (_soc_client->fd == -1){
        handle_error("accept()");
        return 0;
    }

    return 1;
}

int create_peer_client(socket_conn_t* _soc, char* ip, int port){
    _soc->type_sock = 2;
    memset(&(_soc->addr), 0, sizeof(struct sockaddr_in));
    
    _soc->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_soc->fd == -1){
        perror("socket()");
        return 0;
    }

    (_soc->addr).sin_family = AF_INET;
    (_soc->addr).sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &(_soc->addr).sin_addr) <= 0) {
        perror("Invalid address");
        return 0;
    }

    if (connect(_soc->fd, (struct sockaddr *)&_soc->addr, sizeof(_soc->addr)) == -1){
        perror("connect()");
        return 0;
    }
    
    return 1;
}

