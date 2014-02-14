#include <arpa/inet.h>
#include "client.h"
#include "error.h"

#ifndef SERVER_H
#define SERVER_H

typedef struct 
{
        int port;
        int listener_d;
        client *clients;
        struct sockaddr_in name;
} server;

server* serverCreate(int port);
void serverStart(server* srv);
#endif
