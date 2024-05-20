/**
 * @file playlist.h
 * @brief Header file for playlist related functions.
 */

#pragma once
#include "list.h"

typedef struct Playlist Playlist; /**< Playlist structure. */

/**
 * @brief Gets the name of a playlist.
 * 
 * @param playlist The playlist to get the name from.
 * @return The name of the playlist.
 */
char *playlist_get_name(Playlist *playlist);

/**
 * @brief Gets the songs in a playlist.
 * 
 * @param playlist The playlist to get the songs from.
 * @return A list of songs in the playlist.
 */
List *playlist_get_songs(Playlist *playlist);

/**
 * @brief Creates a new playlist.
 * 
 * @param name The name of the new playlist.
 * @return A pointer to the newly created playlist.
 */
Playlist *playlist_create(char *name);

/**
 * @brief Deletes a playlist.
 * 
 * @param playlist The playlist to be deleted.
 */
void playlist_delete(Playlist *playlist);