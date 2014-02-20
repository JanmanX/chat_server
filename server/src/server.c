#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
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
        server->sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        check(server->sock_fd != -1, "Can't open socket");

        server->running = 1;

        memset(&server->serv_addr, '0', sizeof(server->serv_addr));
        server->serv_addr.sin_family = AF_INET;
        server->serv_addr.sin_port = (in_port_t)htons(port);
        server->serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

        int c = bind(server->sock_fd, 
                        (struct sockaddr*)&server->serv_addr, 
                        sizeof(server->serv_addr));

        check(c!=-1, "Can't bind socket");

        check(listen(server->sock_fd, 10) != -1, "Can't listen");

        // Make incoming socket non-blocking
        check(fcntl(server->sock_fd, F_SETFL, O_NDELAY)>=0, 
                        "Cannot make socket non-blocking");


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
        int incomming_fd;
        struct sockaddr_storage client_addr;
        unsigned int address_size = sizeof(client_addr);


        log_info("Server_listen started");

        //Blocking
        //TODO: Read and implement: http://beej.us/guide/bgnet/output/html/multipage/advanced.html#blocking
        while(server->running)
        { 
               incomming_fd = accept(server->sock_fd,
                                (struct sockaddr*)&client_addr,
                                &address_size);

               if(incomming_fd == -1)
               {
                       sleep(10);
            
                        if(server->running == 0)
                            return;
                       continue;
               }

                Client *c = client_create();
                check_mem(c);

                c->connect_d = incomming_fd;
                c->client_addr = client_addr;
 
               char *msg = "Connected...\n";
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

        //        

        // TODO: Close(client_socket)

        close(server->sock_fd);

        log_info("Server closed");

        //      free(server);
}
