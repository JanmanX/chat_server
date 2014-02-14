#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>

typedef struct s_client 
{
        int client_d;

        struct s_client *next;
        struct s_client *prev;
} client;

client* create_client();
void delete_client(client* c);
client* first_client(client* c);
client* last_client(client* c);
client* insert_client(client* list, client* c);
client* remove_client(client* c);
void free_clients(client* c);
#endif
