#include <stdlib.h>
#include <unistd.h>

#include "client.h"

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
