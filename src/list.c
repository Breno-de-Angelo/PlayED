#include "list.h"

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

List *create_list()
{

}

void append(List *list, void *data)
{

}

void delete_list(List *list)
{

}
