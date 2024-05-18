#pragma once

typedef struct List List;

List *list_create();
void list_append(List *list, void *data);
void list_delete(List *list);
void list_remove(List *list, void *data);
void *list_iterator(List *list, void *function(void *element, void *data), void *data);
int list_size(List *list);