#pragma once

#include "list.h"

void write_playlists(List *users_list, char *output_refactored_playlists_directory);
void write_summary(List *users_list, char *output_summary_file_path);
void write_similarity(List *users_list, char *output_similarity_file_path);
void create_directory(char *path);