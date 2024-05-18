#include "user.h"
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_PATH   1000


struct User
{
    char *name;
    List *playlists;
    List *friends;
};


User *user_create(char *name)
{
    User *user = malloc(sizeof(User));
    user->name = strdup(name);
    user->playlists = list_create();
    user->friends = list_create();
    return user;
}

void user_delete(User *user)
{
    free(user->name);
    list_delete(user->playlists);
    list_delete(user->friends);
    free(user);
}

char *user_get_name(User *user)
{
    return user->name;
}

List *user_get_playlists(User *user)
{
    return user->playlists;
}

List *user_get_friends(User *user)
{
    return user->friends;
}

User *user_find_by_name(List *users_list, char *name)
{
    void *prev_user = NULL;
    User *user = NULL;
    while ((user = list_iterate(users_list, &prev_user)) != NULL)
    {
        if (strcmp(user_get_name(user), name) == 0)
        {
            break;
        }
    }
    return user;
}