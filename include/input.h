#pragma once
#include "list.h"

void read_friendship(char *path, List *users_list);
void read_playlists(char *playlist_file_path, char* playlists_directory, List *users_list);