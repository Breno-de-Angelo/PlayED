/**
 * @file song.h
 * @brief Header file for song related functions.
 */

#pragma once
#include "list.h"

typedef struct Song Song; /**< Song structure. */

/**
 * @brief Creates a new song.
 * 
 * @param artist The artist of the song.
 * @param song The name of the song.
 * @return A pointer to the newly created song.
 */
Song *song_create(char *artist, char *song);

/**
 * @brief Deletes a song.
 * 
 * @param song The song to be deleted.
 */
void song_delete(Song *song);

/**
 * @brief Gets the artist of a song.
 * 
 * @param song The song to get the artist from.
 * @return The artist of the song.
 */
char *song_get_artist(Song *song);

/**
 * @brief Gets the name of a song.
 * 
 * @param song The song to get the name from.
 * @return The name of the song.
 */
char *song_get_name(Song *song);