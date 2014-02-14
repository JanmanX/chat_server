#include <myunit.h>
#include "list.h"

char* test_list_create()
{
        List *l = List_create();
        myunit_assert(l != NULL, "List_create() returned NULL");
        myunit_assert(List_count(l) == 0, "List_count() != 0");
        myunit_assert(l->first == NULL, "list->first != NULL");
        myunit_assert(l->last == NULL, "list->last != NULL");

        return NULL;
}

char* test_list_destroy()
{
        List *l = List_create();
        int a = 10;
        List_push(l, &a);
        List_destroy(l);

        //myunit_assert(l == NULL, "List != NULL after destroy()");
        //myunit_assert(l->first == NULL, "list->next != NULL");
        //myunit_assert(l->last == NULL, "list->last != NULL");

        return NULL;
}

char* test_list_clear()
{
        List *list = List_create();

        int i = 0;
        for(; i < 10; i++)
        {
                int *a = malloc(sizeof(int));
                *a = i;
                List_push(list, a);            
        }

        // Clear the List
        List_clear(list);

        LIST_FOREACH(list, first, next, cur)
        {
                myunit_assert(cur->value == NULL, "value not NULL!");
        }
        return NULL;
}

char* test_list_clear_destroy()
{
        // welp
        myunit_assert(test_list_clear() == NULL, "test_List_clear()");
        myunit_assert(test_list_destroy() == NULL, "test_List_destroy()");
        return NULL;
}

char* test_list_count()
{
        List *l = List_create();
        int i = 300;
        for(; i > 0; --i)
        {
                int *a = malloc(sizeof(int));
                *a = i;
                List_push(l, a);
        }

        myunit_assert(List_count(l) == 300, "List_count should be 300!");
        return NULL;
}

char* test_list_first()
{
        List *l = List_create();
        int i = 1337;
        for(; i < 1400; ++i)
        {
                int *a = malloc(sizeof(int));
                *a = i;
                List_push(l, a);
        }

        myunit_assert(*(int*)(l->first->value) == 1337, "First value in list is not 1337");

        return NULL;
}

char* test_list_last()
{
        List *l = List_create();
        int i = 1337;
        for(; i < 1400; ++i)
        {
                int *a = malloc(sizeof(int));
                *a = i;
                List_push(l, a);
        }

        myunit_assert(*(int*)(l->last->value) == 1399, "First value in list is not 1337");


        return NULL;
}

char* test_list_push()
{
        List *list = List_create();
        int *a = (int*)malloc(sizeof(int));
        *a = 10;

        List_push(list, a);

        myunit_assert(*(int*)list->first->value == 10, "list->first->value != 10");
        myunit_assert(*(int*)list->last->value == 10, "list->last->value != 10");
        myunit_assert(List_count(list) == 1, "List_count(list) != 1");

        return NULL;
}

char* test_list_pop()
{
        List *list = List_create();
        int *a = (int*)malloc(sizeof(int));
        *a = 10;

        List_push(list, a);

        int *b = List_pop(list);

        myunit_assert(*b == 10, "*b != 10");
        myunit_assert(List_count(list) == 0, "List_count(...) != 0");

        return NULL;
}

char* test_list_remove()
{
        // ?
        return NULL;
}

char* test_list_remove_specific()
{
        List *list = List_create();
        int *a = malloc(sizeof(int));
        int *b = malloc(sizeof(int));
        int *c = malloc(sizeof(int));
        *a = 10;
        *b = 20;
        *c = 30;

        List_push(list, a);
        List_push(list, b);
        List_push(list, c);

        List_remove_specific(list, b);

        myunit_assert(List_count(list) == 2, "List size not 2");

        return NULL;
}

char* test_all()
{
        myunit_start_tests();

        myunit_test(test_list_create);
        myunit_test(test_list_destroy);
        myunit_test(test_list_clear);
        myunit_test(test_list_clear_destroy);
        myunit_test(test_list_count);
        myunit_test(test_list_first);
        myunit_test(test_list_last);
        myunit_test(test_list_push);
        myunit_test(test_list_pop);
        myunit_test(test_list_remove);
        myunit_test(test_list_remove_specific);

        return NULL;
}

RUN_TESTS(test_all)


