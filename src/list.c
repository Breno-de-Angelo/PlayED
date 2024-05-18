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
    int length;
};

List *list_create()
{
    List *list = malloc(sizeof(List));
    list->first = NULL;
    list->last = NULL;
    list->length = 0;
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
        list->length++;
        return;
    }
    // Non-empty list
    node->prev = list->last;
    node->next = NULL;
    list->last = list->last->next = node;
    list->length++;
    return;
}

int list_private_iterator(List *list, int function(Node *node, void *data), void *data)
{
    Node *p = list->first;
    Node *aux = NULL;
    while (p)
    {
        aux = p;
        p = p->next;
        if (function(aux, data))
        {
            return 1;
        }
    }
    return 0;
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
            list->length--;
            return;
        }
        return;
    }
    if (list->first->data == data)
    {
        list->first = list->first->next;
        free(list->first->prev);
        list->first->prev = NULL;
        list->length--;
        return;
    }
    if (list->last->data == data)
    {
        list->last = list->last->prev;
        free(list->last->next);
        list->last->next = NULL;
        list->length--;
        return;
    }
    if (list_private_iterator(list, list_remove_element, data))
    {
        list->length--;
    }
    return;
}

int list_size(List *list)
{
    return list->length;
}

void *list_iterate(List *list, void **prev)
{
    Node *prev_node = (Node *) *prev;
    if (list->first == NULL)
    {
        return NULL;
    }
    if (prev_node == NULL)
    {
        *prev = list->first;
        return list->first->data;
    }
    if (prev_node->next == NULL)
    {
        return NULL;
    }
    *prev = prev_node->next;
    return prev_node->next->data;
}
