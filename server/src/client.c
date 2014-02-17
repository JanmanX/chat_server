#include <stdlib.h>

#include "client.h"

Client *client_create(int cd)
{
        Client *c = calloc(1, sizeof(Client)); // calloc for cleared memory
        check(c != NULL, "calloc returned NULL");

        c->connect_d = cd;

        return c;

error:
        return NULL;
}

void client_destroy(Client *c)
{
  
}
