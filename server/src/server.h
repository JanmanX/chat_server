#ifndef SERVER_H
#define SERVER_H

#include <pthread.h>

#include "double_list/list.h"

typedef struct{
        List *client_list;
        int port;
        int listener_d;
       
        volatile int running; 
        pthread_t pthread;
        pthread_mutex_t server_lock;        
}Server;

Server *Server_create();
void Server_open(Server* server, int port);
void Server_close(Server* server);
void Server_listen(Server* server);
#endif
