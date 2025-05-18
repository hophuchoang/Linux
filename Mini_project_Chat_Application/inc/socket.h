#ifndef SOCKET_H
#define SOCKET_H

#include "sock_defs.h"

void get_ip(const socket_conn_t *peer, char *ip);

int get_port(socket_conn_t *peer);

int create_server(socket_conn_t* _soc, char* ip, int port);

int check_new_peer (int fd, socket_conn_t* _soc_client);

int create_peer_client(socket_conn_t* _soc, char* ip, int port);

#endif // SOCKET_H


