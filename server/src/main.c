#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "server.h"
#include "error.h"

int main(int argc, char **argv)
{
        Server *s = Server_create();
        Server_open(s, 31337);
}

