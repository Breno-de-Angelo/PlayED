#pragma once
#include "list.h"
#include "playlist.h"

typedef struct User User;

User *user_create(char *nome);
void user_delete(User *user);
User *list_find_user(List *users_list, char *name);
void user_add_friendship(User *user1, User *user2);
void user_append_playlist(User *user, Playlist *playlist);
void list_user_update_playlist(List *users_list);