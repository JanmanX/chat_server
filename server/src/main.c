#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <arpa/inet.h>

#include "client.h"
#include "server.h"
#include "error.h"

int main(int argc, char **argv)
{
        server *chat_server = serverCreate(31337);

        if(chat_server == NULL) 
                error("PENIS");

        serverStart(chat_server);
}

