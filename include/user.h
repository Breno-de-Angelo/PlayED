#pragma once
#include "list.h"

typedef struct User User;

User *user_create(char *nome);
void user_delete(User *user);
char *user_get_name(User *user);
List *user_get_playlists(User *user);
List *user_get_friends(User *user);
User *user_find_by_name(List *users_list, char *name);




User *list_find_user(List *users_list, char *name);
void user_add_friendship(User *user1, User *user2);
void user_append_playlist(User *user, Playlist *playlist);
void list_user_update_playlist(List *users_list);
void list_user_print(List *list);
void list_user_print_playlists(List *list);
void list_user_write_played(List *users_list, char* path);
void list_user_write_playlists(List *users_list, char* path);
void list_user_write_similarity(List *users_list, char *output_similarity_file_path);