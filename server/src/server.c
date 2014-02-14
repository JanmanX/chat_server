#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>

#include "server.h"

server* serverCreate(int port)
{
        server *srv = (server*)malloc(sizeof(server));
        assert(srv != NULL && "server == NULL");        
        srv->port = port;
        srv->name.sin_family = PF_INET;
        srv->name.sin_port = (in_port_t)htons(port);
        srv->name.sin_addr.s_addr = htonl(INADDR_ANY);
        return srv;
}

void serverStart(server* srv)
{
        srv->listener_d = socket(PF_INET, SOCK_STREAM, 0);
        if(srv->listener_d == -1)
                error("Can't open socket");

        int c = bind(srv->listener_d,
                        (struct sockaddr*) &srv->name,
                        sizeof(srv->name));
        if(c == -1)
                error("Can't bind to socket");

        if(listen(srv->listener_d, 10) == -1)
                error("Can't listen");

        client *new_client = create_client();
        struct sockaddr_storage client_addr;
        unsigned int address_size = sizeof(client_addr);
        new_client->client_d = accept(srv->listener_d, 
                        (struct sockaddr *)&client_addr,

                        &address_size);
        if(new_client->client_d == -1)
                error("Can't open secondary socket");

        char *msg = "Connected...\n";
        if(send(new_client->client_d, msg, strlen(msg), 0) == -1)
                error("send");
}

void serverClose(server* srv)
{

}

