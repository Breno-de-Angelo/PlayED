/**
 * @file list.h
 * @brief File containing the list data structure and its operations.
 */

#pragma once

/**
 * @brief A structure to represent a list.
 */
typedef struct List List;

/**
 * @brief Creates a new list.
 * 
 * @return A pointer to the newly created list.
 */
List *list_create();

/**
 * @brief Appends data to the end of the list.
 * 
 * @param list A pointer to the list.
 * @param data The data to be appended.
 */
void list_append(List *list, void *data);

/**
 * @brief Deletes the list.
 * 
 * @param list A pointer to the list to be deleted.
 */
void list_delete(List *list);

/**
 * @brief Removes the specified data from the list.
 * 
 * @param list A pointer to the list.
 * @param data The data to be removed.
 */
void list_remove(List *list, void *data);

/**
 * @brief Returns the size of the list.
 * 
 * @param list A pointer to the list.
 * @return The size of the list.
 */
int list_size(List *list);

/**
 * @brief Iterates over the list.
 * 
 * @param list A pointer to the list.
 * @param prev A pointer to the previous element.
 * @return The next element in the list.
 */
void *list_iterate(List *list, void **prev);