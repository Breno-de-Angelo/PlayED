#pragma once

typedef struct List List;

List *list_create();
void list_append(List *list, void *data);
void list_delete(List *list);
void list_remove(List *list, void *data);
int list_size(List *list);
void *list_iterate(List *list, void **prev);