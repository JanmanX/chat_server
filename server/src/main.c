#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "server.h"
#include "error.h"

int main(int argc, char **argv)
{
        Server *s = Server_create();
        Server_open(s, 31338);

        // Server is running.
        sleep(60); // SLeep for 1 minute
        Server_close(s);

        return 0;        
}

