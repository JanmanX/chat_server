#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "double_list/list.h"
#include "dbg.h"
#include "server.h"
#include "client.h"

Server *Server_create()
{
        Server *server = calloc(1, sizeof(Server));
        check_mem(server);

        return server;
error:
        return NULL;
}

void Server_open(Server *server, int port)
{
   server->port = port;
    server->listener_d = socket(PF_INET, SOCK_STREAM, 0);
    check(server->listener_d != -1, "Can't open socket");
    
    server->server_lock = PTHREAD_MUTEX_INITIALIZER;    
    server->running = 1;


    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    int c = bind(server->listener_d, (struct sockaddr*)&name, sizeof(name));
    check(c!=-1, "Can't bind socket");

    check(listen(server->listener_d, 10) != -1, "Can't listen");


    // Create a new thread and start it
    pthread_create(&server->listen_thread, 
                    NULL, 
                    Server_listen,
                    (void*)server);

error:
    return;
}

void* Server_listen(Server *server)
{
        while(server->running)
        { 
                Client *c = client_create();
                unsigned int address_size = sizeof(c->client_addr);
                int foo = accept(server->listener_d, (struct sockaddr*)&c->client_addr, &address_size);
                check(foo != -1, "Can't open client socket");

                char *msg = "Connected...";
                check(send(c->connect_d, msg, strlen(msg), 0) != -1, "Cannot send message");
        }
error:
        return;      
}

void Server_close(Server *server)
{
        void *result = NULL;
        pthread_join(server->listen_thread, &result);

        List_clear_destroy(server->client_list);

        // TODO: Close server
        // TODO: Close(client_socket)


        free(server);
}
