#include <stdlib.h>

#include "client.h"

Client *client_create()
{
        Client *c = calloc(1, sizeof(Client)); // calloc for cleared memory
        check(c != NULL, "calloc returned NULL");

        return c;

error:
        return NULL;
}

void client_destroy(Client *c)
{
  
}
