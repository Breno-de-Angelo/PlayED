#pragma once
#include "list.h"

typedef struct User User;

User *user_create(char *nome);
void user_delete(User *user);
char *user_get_name(User *user);
List *user_get_playlists(User *user);
List *user_get_friends(User *user);
User *user_find_by_name(List *users_list, char *name);