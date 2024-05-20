/**
 * @file user.h
 * @brief Header file for user related functions.
 */

#pragma once
#include "list.h"

typedef struct User User; /**< User structure. */

/**
 * @brief Creates a new user.
 * 
 * @param name The name of the user.
 * @return A pointer to the newly created user.
 */
User *user_create(char *name);

/**
 * @brief Deletes a user.
 * 
 * @param user The user to be deleted.
 */
void user_delete(User *user);

/**
 * @brief Gets the name of a user.
 * 
 * @param user The user to get the name from.
 * @return The name of the user.
 */
char *user_get_name(User *user);

/**
 * @brief Gets the playlists of a user.
 * 
 * @param user The user to get the playlists from.
 * @return A list of playlists of the user.
 */
List *user_get_playlists(User *user);

/**
 * @brief Gets the friends of a user.
 * 
 * @param user The user to get the friends from.
 * @return A list of friends of the user.
 */
List *user_get_friends(User *user);

/**
 * @brief Finds a user by name from a list of users.
 * 
 * @param users_list The list of users to search from.
 * @param name The name of the user to find.
 * @return A pointer to the user if found, NULL otherwise.
 */
User *user_find_by_name(List *users_list, char *name);

/**
 * @brief Sets the playlist for a user.
 * 
 * @param user The user to set the playlist for.
 * @param playlist The playlist to be set.
 */
void user_set_playlist(User *user, List *playlist);