#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "server.h"
#include "error.h"
#include "dbg.h"

int main(int argc, char **argv)
{
        if(argc < 2)
        {
            log_err("Not enough arguments. Missing port number");
        }
    
        int port = atoi(argv[1]);
        if(port < 1024 || port > 65536)
        {
            log_err("Invalid port number: %d", port);
        }

        Server *s = Server_create();
        Server_open(s, port);

        // Server is running.
        sleep(60); // SLeep for 1 minute
        Server_close(s);

        return 0;        

error:
        return -1;
}

