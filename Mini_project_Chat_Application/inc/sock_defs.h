#ifndef SOCK_DEFS_H
#define SOCK_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <netinet/in.h>  // struct sockaddr_in

#define LISTEN_BACKLOG 5
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

typedef struct {
    int type_sock;
    int fd;                                       
    struct sockaddr_in addr;    
} socket_conn_t;

#ifdef __cplusplus
}
#endif

#endif // SOCK_DEFS_H
