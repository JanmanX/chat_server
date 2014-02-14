#include <stdio.h>
#include <stdlib.h>

#include "error.h"

void error(char *msg)
{
        fprintf(stderr, "%s", msg);
        exit(-1);
}
