#include "list.h"
#include <stdlib.h>

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
    size_t element_size;
};

List *create_list()
{
    List *list = malloc(sizeof(List));
    list->first = NULL;
    list->last = NULL;
    return list;
}

void append(List *list, void *data)
{
    Node *node = malloc(sizeof(Node));
    node->data = malloc(list->element_size);
    if (list->first == NULL)
    {
        // Empty list
        list->first = list->last = node;
        node->prev = node->next = NULL;
        return;
    }
    // Non-empty list
    node->prev = list->last;
    list->last = list->last->next = node;
    return;
}

void delete_list(List *list)
{
    free(list);
}
