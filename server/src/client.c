#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <string.h>

#include "client.h"


#define BUFFER_SIZE 1024

Client *client_create()
{
        Client *c = calloc(1, sizeof(Client)); // calloc for cleared memory
        check(c != NULL, "calloc returned NULL");

        return c;

error:
        return NULL;
}

// Closes the client and frees the resources
void client_destroy(Client *c)
{
        check(close(c->connect_d) != -1, "Cannot close client->connect_d");

        free(c);
        c = NULL;

error:
    return;
}

void *client_recv(struct client* c)
{
        // Make incoming socket non-blocking
        check(fcntl(c->connect_d, F_SETFL, O_NDELAY)>=0, 
                        "Cannot make socket non-blocking");

        // Create buffer
        char* buffer = calloc(BUFFER_SIZE, sizeof(char));
        check_mem(buffer);
        
        int len = 0;

        while(1)
        {
            
            len = recv(c->connect_d, buffer, sizeof(buffer), 0);
            if(len > 0)
            {
                fprintf(stdout, "%s", buffer);
                memset(buffer, 0, sizeof(buffer));
                len = 0;
            }       
        }

error:
    return;
}
