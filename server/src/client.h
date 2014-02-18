#ifndef CLIENT_H
#define CLIENT_H

#include <sys/socket.h>

#include "dbg.h"

struct client {
        int connect_d;
};
typedef struct client Client;

Client *client_create();
void client_destroy(Client* c);

#endif
