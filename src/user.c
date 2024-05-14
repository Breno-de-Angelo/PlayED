#include "list.h"
#include "user.h"
#include "song.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void *find_user(void *element, void *data)
{
    User *user = (User *) element;
    char *name = (char *) data;
    if (!strcmp(name, user->name))
    {
        return user;
    }
    return NULL;
}

User *list_find_user(List *users_list, char *name)
{
    User *user = (User *) list_iterator(users_list, find_user, name);
    return user;
}

void user_add_friendship(User *user1, User *user2)
{
    list_append(user1->friends, user2);
    list_append(user2->friends, user1);
}

void user_add_song(User *user, char *artist, char *song)
{
    Song *new_song = song_create(artist, song);
    list_append(user->playlists, new_song);
}
