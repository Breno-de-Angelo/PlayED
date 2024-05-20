/**
 * @file input.h
 * @brief Header file for input related functions.
 */

#pragma once
#include "list.h"
#include <stdio.h>

#define MAX_LINE_LENGTH 1000 /**< Maximum length of a line. */
#define MAX_FILE_PATH 1000 /**< Maximum length of a file path. */

/**
 * @brief Reads friendship data from a file and populates a list of users.
 * 
 * @param path Path to the file containing friendship data.
 * @param users_list List of users to be populated.
 */
void read_friendship(char *path, List *users_list);

/**
 * @brief Reads playlist data from a file and populates a list of users.
 * 
 * @param playlist_file_path Path to the file containing playlist data.
 * @param playlists_directory Directory containing playlists.
 * @param users_list List of users to be populated.
 */
void read_playlists(char *playlist_file_path, char* playlists_directory, List *users_list);

/**
 * @brief Opens a file in a specified mode.
 * 
 * @param path Path to the file to be opened.
 * @param mode Mode in which the file should be opened.
 * @return Pointer to the opened file.
 */
FILE *open_file(char *path, char *mode);