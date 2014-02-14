#include <assert.h>
#include <stdlib.h>

#include "client.h"

client* create_client()
{
        client* c = (client*)malloc(sizeof(client));

        assert(c != NULL && "Cannot malloc client");

        c->next = NULL;
        c->prev = NULL;

        return c;    
}

void delete_client(client *c)
{
        free(c);
}

client* first_client(client* c)
{
        if(c == NULL)
                return NULL;

        if(c->prev != NULL)
                return first_client(c->prev);
        else
                return c;
}

client* last_client(client* c)
{
        if(c == NULL)   
                return NULL;

        if(c->next != NULL)
                return last_client(c->next);
        else
                return c;
}

client* insert_client(client* list, client* new_client)
{
        assert(new_client != NULL && "new_client from insert_client() IS NULL!");

        client* c = last_client(list);

        if(c != NULL)
        {
                c->next = new_client;
                new_client->prev = c;
        }
        return new_client;
}

client* remove_client(client* c)
{
        assert(c != NULL && "client c in remove_client() cant be NULL");

        if(c->prev != NULL && c->next != NULL)
        {
                c->prev->next = c->next;
                c->next->prev = c->prev;
                return first_client(c->prev);
        }

        if(c->prev != NULL && c->next == NULL)
        {
                c->prev->next = NULL;
                return first_client(c->prev);
        }
        if(c->next != NULL && c->prev == NULL)
        {
                c->next->prev = NULL;
                return c->next;
        }
        else return NULL;
}

void free_clients(client* clients)
{

}
