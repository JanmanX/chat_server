#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <pthread.h>

#include "double_list/list.h"

typedef struct{
        List *client_list;
        int port;
        int sock_fd;

        struct sockaddr_in serv_addr;
       
        volatile int running; 
        pthread_t listen_thread;
}Server;

Server *Server_create();
void Server_open(Server* server, int port);
void Server_close(Server* server);
void* Server_listen(Server* server);
#endif
