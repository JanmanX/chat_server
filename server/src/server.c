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

// Allocates and returns a new server.
// Returns NULL on error
Server *Server_create()
{
        Server *server = calloc(1, sizeof(Server));
        check_mem(server);

        server->client_list = List_create();
        check_mem(server->client_list);

        return server;
error:
        return NULL;
}

// Opens socket and starts listening for incomming connections in a separate 
// thread.
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


        // Sets the server socket to listen
        check(listen(server->sock_fd, 10) != -1, "Can't listen");

        // Make incoming socket non-blocking
        check(fcntl(server->sock_fd, F_SETFL, O_NDELAY)>=0, 
                        "Cannot make socket non-blocking");


        // Create a new thread and start it
        pthread_create(&server->listen_thread, 
                        NULL, 
                        (void*)Server_listen,
                        (void*)server);

        return;
error:
        log_warn("Error occured while opening server");
        return;
}

// Listens for incoming connections until server->running == 0.
void* Server_listen(Server *server)
{
        int incomming_fd;
        struct sockaddr_storage client_addr;
        unsigned int address_size = sizeof(client_addr);

        log_info("Server_listen started");


        while(server->running)
        { 
                incomming_fd = accept(server->sock_fd,
                                (struct sockaddr*)&client_addr,
                                &address_size);

                if(incomming_fd == -1)
                {
                        sleep(1);

                        continue;
                }

                // Client connected, create a new client struct, send a message
                // to the client and start listening thread
                struct client *c = client_create();
                check_mem(c);

                c->connect_d = incomming_fd;
                c->client_addr = client_addr;

                char *msg = "Connected...\n";
                check(send(c->connect_d, msg, strlen(msg), 0) != -1, 
                                "Cannot send message");

                List_push(server->client_list, c);

                c->running = 1;

                // Create a new thread and start it
                pthread_create(&c->recv_thread, 
                                NULL, 
                                (void*)client_recv, 
                                (void*)c);

                log_info("A new client just joined the server");
                log_info("Number of clients online: %d",
                                List_count(server->client_list));
        }

        log_info("Server_listen() closing");
error:
        return;      
}

// Sends a message to ALL clients on connected.
// TODO: If send fails, remove client from list.
void *Server_send(Server* server, char* msg)
{
        log_info("Streaming message: ");

        int len = 0;
        struct client* c;

        LIST_FOREACH(server->client_list, first, next, cur)
        {
                c = (struct client*)cur->value;

                // Send the message and record how many bytes were sent
                len = send(c->connect_d, msg, BUFFER_SIZE,0);

                if(len == 0)
                {
                        log_info("No bytes were sent");

                        // TODO: REMOVE CLIENT FROM LIST
                        c->running = 0;

                        // Wait for the thread to finish.
                        void* result = NULL;                    
                        pthread_join(c->recv_thread, &result);

                        client_destroy(c);
                        List_remove_specific(server->client_list, (void*)c);
                }
        }
}

// Closes the server and frees all ressources associated with it.
void Server_close(Server *server)
{
        log_info("Closing server...");

        // Signals the server termination
        server->running = 0;

        // Temporary client instance
        struct client *c;

        // Result of the listening thread. As of now, nothing is returned.
        void *result = NULL;

        // wait for listen_thread to exit
        pthread_join(server->listen_thread, &result);

        // TODO: split into more loops to increase speed dramatically
        LIST_FOREACH(server->client_list, first, next, cur)
        {
                c = (struct client*)cur->value;
                c->running = 0;

                // Wait for the thread to finish.
                pthread_join(c->recv_thread, &result);

                // Free client resources
                client_destroy(cur->value);
        }

        // Free list
        List_destroy(server->client_list);

        // Close listening socket
        close(server->sock_fd);

        log_info("Server closed");

        // Free server
        free(server);
}
