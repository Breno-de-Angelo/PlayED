#pragma once

typedef struct List List;

List *create_list();
void append(List *list, void *data);
void delete_list(List *list);