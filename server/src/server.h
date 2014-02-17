#ifndef SERVER_H
#define SERVER_H

#include "double_list/list.h"

typedef struct{
        List *client_list;
        int port;
        int listener_d;
}Server;

Server *Server_create();
void Server_open(Server* server, int port);
void Server_close(Server* server);
void Server_listen(Server* server);
#endif
