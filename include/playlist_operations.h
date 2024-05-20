/**
 * @file playlist_operations.h
 * @brief Header file for playlist operations.
 */

#pragma once
#include "list.h"

/**
 * @brief Refactors playlists for a list of users.
 * 
 * @param users_list List of users whose playlists will be refactored.
 */
void refactor_playlists(List *users_list);

/**
 * @brief Merges playlists for a list of users.
 * 
 * @param users_list List of users whose playlists will be merged.
 */
void merge_playlists(List *users_list);

/**
 * @brief Destroys a list of users.
 * 
 * @param users_list List of users to be destroyed.
 */
void list_destroy(List *users_list);

/**
 * @brief Checks if a song exists in a list.
 * 
 * @param songs The list of songs to check.
 * @param artist The artist of the song.
 * @param song The name of the song.
 * @return 1 if the song exists, 0 otherwise.
 */
int check_if_song_exists(List *songs, char *artist, char *song);