#pragma once
#include "list.h"
#include "user.h"

void txt_read_friendship(char *path, List *users_list);
void txt_read_playlists(char *playlist_file_path, char* playlists_directory, List *users_list);
