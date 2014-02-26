#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <string.h>

#include "client.h"

struct client *client_create()
{
        struct client *c = calloc(1, sizeof(struct client)); // calloc for cleared memory
        check(c != NULL, "calloc returned NULL");

        return c;

error:
        return NULL;
}

// Closes the client and frees the resources
void client_destroy(struct client *c)
{
        check(close(c->connect_d) != -1, "Cannot close client->connect_d");

        free(c);
        c = NULL;

error:
        return;
}

void *client_recv(struct client* c)
{
        log_info("Starting listen loop for client");

        // Make incoming socket non-blocking
        check(fcntl(c->connect_d, F_SETFL, O_NDELAY)>=0, 
                        "Cannot make client socket non-blocking");

        // Create buffer
        char* buffer = calloc(BUFFER_SIZE, sizeof(char));
        check_mem(buffer);

        int len = 0;

        while(c->running == 1)
        { 
                len = recv(c->connect_d, buffer, BUFFER_SIZE, 0);
                if(len > 0)
                {
                        printf("%s", buffer);
                        memset(buffer, 0, sizeof(buffer));
                        len = 0;
                }
                sleep(1); 

        }

        log_info("Client recv_thread closed");
error:
        return;
}
