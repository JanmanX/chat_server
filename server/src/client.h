#ifndef CLIENT_H
#define CLIENT_H

#include <sys/socket.h>

#include "server.h"
#include "dbg.h"

#define BUFFER_SIZE 2048 // Should be enough.

struct client {
        int connect_d;
        volatile int running;

		Server* owner;
		struct sockaddr_storage client_addr;
		pthread_t recv_thread;
};

struct client *client_create();
void client_destroy(struct client* c);
void* client_recv(struct client* c);

#endif 
