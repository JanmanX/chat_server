#ifndef SERVER_H
#define SERVER_H

#include "double_list/list.h"

struct server {
        List *client_list;
        int port;
        int listener_d;
};
typedef struct server Server;

Server *Server_create();
void Server_open(Server* server, int port);
void Server_close(Server* server);

#endif
