#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "server.h"
#include "error.h"
#include "dbg.h"

int main(int argc, char **argv)
{
        check(argc>1, "Argument for port number missing");

        int port = atoi(argv[1]);
        if(port < 1024 || port > 65536)
        {
            log_err("Invalid port number: %d", port);
            goto error;
        }

        Server *s = Server_create();
        Server_open(s, port);

        // Server is running.
        sleep(30); // SLeep for 1 minute
        Server_close(s);

        return 0;        

error:
        return -1;
}

