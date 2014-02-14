#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main(int argc, char **argv)
{
List *list = List_create();
int a = 10;
int b = 20;
int c = 30;

int *pa = &a;
int *pb = &b;
int *pc = &c;

List_push(list, pa);
List_push(list, pb);
List_push(list, pc);
printf("%d\n", List_count(list));

int *d = List_pop(list);
int *e = List_pop(list);
int *f = List_pop(list);

printf("%d\n", *d);
printf("%d\n", *e);
printf("%d\n", *f);

return 0;
}
