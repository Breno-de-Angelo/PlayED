#pragma once
#include "list.h"

typedef struct User User;

User *user_create(char *nome);
void user_delete(User *user);
User *list_find_user(List *users_list, char *name);
void user_add_friendship(User *user1, User *user2);
void user_add_song(User *user, char *artist, char *song);