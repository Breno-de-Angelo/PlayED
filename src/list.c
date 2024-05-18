#include "list.h"
#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;
struct Node
{
    void *data;
    Node *next;
    Node *prev;
};

struct List
{
    Node *first;
    Node *last;
};

List *list_create()
{
    List *list = malloc(sizeof(List));
    list->first = NULL;
    list->last = NULL;
    return list;
}

void list_append(List *list, void *data)
{
    Node *node = malloc(sizeof(Node));
    node->data = data;
    if (list->first == NULL)
    {
        // Empty list
        list->first = list->last = node;
        node->prev = node->next = NULL;
        return;
    }
    // Non-empty list
    node->prev = list->last;
    node->next = NULL;
    list->last = list->last->next = node;
    return;
}

void list_private_iterator(List *list, int function(Node *node, void *data), void *data)
{
    Node *p = list->first;
    Node *aux = NULL;
    while (p)
    {
        aux = p;
        p = p->next;
        if (function(aux, data))
        {
            return;
        }
    }
}

int list_delete_element(Node *node, void *data)
{
    (void) data;
    free(node);
    return 0;
}

void list_delete(List *list)
{
    list_private_iterator(list, list_delete_element, NULL);
    free(list);
}

int list_remove_element(Node *node, void *data)
{
    if (node->data == data)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        free(node);
        return 1;
    }
    return 0;
}

void list_remove(List *list, void *data)
{
    if (list->first == NULL)
    {
        return;
    }
    if (list->first == list->last)
    {
        if (list->first->data == data)
        {
            free(list->first);
            list->first = NULL;
            list->last = NULL;
            return;
        }
        return;
    }
    if (list->first->data == data)
    {
        list->first = list->first->next;
        free(list->first->prev);
        list->first->prev = NULL;
        return;
    }
    if (list->last->data == data)
    {
        list->last = list->last->prev;
        free(list->last->next);
        list->last->next = NULL;
        return;
    }
    list_private_iterator(list, list_remove_element, data);
}

void *list_iterator(List *list, void *function(void *element, void *data), void *data)
{
    Node *p = list->first;
    Node *aux = NULL;
    void *result;
    while (p)
    {
        aux = p;
        p = p->next;
        result = function(aux->data, data);
        if (result != NULL)
        {
            return result;
        }
    }
    return NULL;
}

void *list_size_count(void *element, void *data)
{
    (void) element;
    int *counter = (int *) data;
    (*counter)++;
    return NULL;
}

int list_size(List *list)
{
    int counter = 0;
    list_iterator(list, list_size_count, &counter);
    return counter;
}
