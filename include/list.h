#pragma once

typedef struct List List;

List *list_create();
void list_append(List *list, void *data, void (*print)(void*));
void list_delete(List *list);
void list_remove(List *list, void *data);
void *list_iterator(List *list, void *function(void *element, void *data), void *data);
// void list_append_int(List *list, int *data);
void list_print(List *list);