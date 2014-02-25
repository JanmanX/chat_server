#ifndef CLIENT_H
#define CLIENT_H

#include <sys/socket.h>

#include "dbg.h"

struct client {
        int connect_d;
        volatile int running;
        struct sockaddr_storage client_addr;
        pthread_t recv_thread;
};
typedef struct client Client;

Client *client_create();
void client_destroy(Client* c);
void* client_recv(struct client* c, volatile int *running);

#endif 
