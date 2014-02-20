#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>

#include "double_list/list.h"
#include "dbg.h"
#include "server.h"
#include "client.h"

pthread_mutex_t server_lock = PTHREAD_MUTEX_INITIALIZER;

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
        server->listener_d = socket(AF_INET, SOCK_STREAM, 0);
        check(server->listener_d != -1, "Can't open socket");

        server->running = 1;

        memset(&server->serv_addr, '0', sizeof(server->serv_addr));
        server->serv_addr.sin_family = AF_INET;
        server->serv_addr.sin_port = (in_port_t)htons(port);
        server->serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

        int c = bind(server->listener_d, 
                        (struct sockaddr*)&server->serv_addr, 
                        sizeof(server->serv_addr));

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
        log_info("Server_listen started");

        while(server->running)
        { 
                Client *c = client_create();
                struct sockaddr_storage client_addr;

                unsigned int address_size = sizeof(client_addr);
                c->connect_d = accept(server->listener_d,
                                (struct sockaddr*)&client_addr,
                                &address_size);

                check(c->connect_d != -1, "Can't open client socket");

                char *msg = "Connected...";
                check(send(c->connect_d, msg, strlen(msg), 0) != -1, 
                                "Cannot send message");
        }

        log_info("Server_listen() closing");
error:
        return;      
}

void Server_close(Server *server)
{
        log_info("Closing server...");

        server->running = 0;
        void *result = NULL;

        // wait for listen_thread to exit
        pthread_join(server->listen_thread, &result);

        // TODO: Close server ( ? )    
        // TODO: Close(client_socket)


        free(server);
}
