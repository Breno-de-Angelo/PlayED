#pragma once
#include "list.h"
#include <stdio.h>

#define MAX_LINE_LENGTH 1000
#define MAX_FILE_PATH 1000

void read_friendship(char *path, List *users_list);
void read_playlists(char *playlist_file_path, char* playlists_directory, List *users_list);
FILE *open_file(char *path, char *mode);