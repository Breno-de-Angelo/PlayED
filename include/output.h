/**
 * @file output.h
 * @brief Header file for output related functions.
 */

#pragma once
#include "list.h"

/**
 * @brief Writes playlists data to a specified directory.
 * 
 * @param users_list List of users to be written.
 * @param output_refactored_playlists_directory Directory where the playlists data should be written.
 */
void write_playlists(List *users_list, char *output_refactored_playlists_directory);

/**
 * @brief Writes summary data to a specified file.
 * 
 * @param users_list List of users to be written.
 * @param output_summary_file_path File path where the summary data should be written.
 */
void write_summary(List *users_list, char *output_summary_file_path);

/**
 * @brief Writes similarity data to a specified file.
 * 
 * @param users_list List of users to be written.
 * @param output_similarity_file_path File path where the similarity data should be written.
 */
void write_similarity(List *users_list, char *output_similarity_file_path);

/**
 * @brief Creates a directory at a specified path.
 * 
 * @param path Path where the directory should be created.
 */
void create_directory(char *path);