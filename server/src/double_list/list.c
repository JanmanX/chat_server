#include <stdlib.h>
#include <dbg.h>

#include "list.h"

// Callocs and returns a new list 
List *List_create()
{
        List *list = calloc(1, sizeof(List));
        check(list != NULL, "Failed to calloc memory"); 
        return list;

error:
        return NULL;
}

// frees all elements in the list (including the list)
void List_destroy(List *list)
{
        check(list != NULL, "list is NULL");

        LIST_FOREACH(list, first, next, cur) 
        {
                if(cur->prev) 
                {
                        free(cur->prev);
                }
        }

        free(list->last);
        free(list);
        //list = NULL; // not working. WHY?!
    
error:
     return;
}

// frees all values in the list
void List_clear(List *list)
{
        LIST_FOREACH(list, first, next, cur)
        {
                free(cur->value);
                cur->value = NULL;
        }
}

// Clears the list and destroys it
void List_clear_destroy(List *list)
{
        check(list != NULL, "list is NULL");
        List_clear(list);
        List_destroy(list);
   
error:
    return;
}

// Pushes a new value into the list
void List_push(List *list, void *value)
{
        ListNode *node = calloc(1,sizeof(ListNode));
        check_mem(node);

        node->value = value;

        if(list->last == NULL)
        {
                list->first = node;
                list->last = node;
        }
        else
        {
                list->last->next = node;
                node->prev = list->last;
                list->last = node;
        }

        list->count++;

error:
        return;
}

// Pops the last value in the list
void *List_pop(List *list)
{
        check(list != NULL, "list is NULL");

        ListNode *node = list->last;
        return node != NULL ? List_remove(list, node) : NULL;

error:
    return NULL;
}

// Removes a specific element from the list
void *List_remove_specific(List *list, void *value)
{
        check(list != NULL, "list is null");

        ListNode *cur = list->first;
        while(cur)
        {
                if(value == cur->value)
                {
                   return List_remove(list, cur);
                }

                cur = cur->next;
        }

error:
        return;
}

void *List_remove(List *list, ListNode *node)
{
        check(list != NULL, "list is NULL");

        void *result = NULL;

        if(node == list->first && node == list->last)
        {
                list->first = NULL;
                list->last = NULL;
        }
        else if(node == list->first)
        {
                list->first = node->next;
                list->first->prev = NULL;
        }
        else if(node == list->last)
        {
                list->last = node->prev;
                list->last->next = NULL;
        }
        else {
                ListNode *after = node->next;
                ListNode *before = node->prev;

                after->prev = before;
                before->next = after;
        }

        list->count--;
        result = node->value;
        free(node);

error:
        return result;
}
