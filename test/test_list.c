#include "list.h"
#include <stdio.h>
// #include <assert.h>

int main()
{
    printf("Teste");
    List *list = list_create();
    int val1 = 3;
    int val2 = 10;
    int val3 = 5;
    list_append_int(list, &val1);
    list_print(list);
    printf("\n\n");
    list_append_int(list, &val2);
    list_print(list);
    printf("\n\n");
    list_append_int(list, &val3);
    list_print(list);
    printf("\n\n");
    list_remove(list, &val2);
    list_print(list);
    printf("\n\n");
    list_remove(list, &val1);
    list_print(list);
    printf("\n\n");
    list_delete(list);
    return 0;
}
