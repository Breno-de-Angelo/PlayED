#include "input.h"
#include "user.h"
#include "song.h"
#include "playlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define MAX_FILE_PATH 1000

FILE *open_file(char *path, char *mode)
{
    FILE *file = fopen(path, mode);
    if (file == NULL)
    {
        printf("Error opening file %s\n", path);
        exit(1);
    }
    return file;
}

void remove_trailing_character(char *str, char c)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == c)
    {
        str[len - 1] = '\0';
    }
}

void read_users(FILE *file, List *users_list)
{
    char buffer[MAX_LINE_LENGTH];
    char *token;
    char *saveptr;

    if (fgets(buffer, MAX_LINE_LENGTH, file) != NULL)
    {
        token = strtok_r(buffer, ";", &saveptr);
        while (token != NULL)
        {
            remove_trailing_character(token, '\n');
            User *user = user_create(token);
            list_append(users_list, user);
            token = strtok_r(NULL, ";", &saveptr);
        }
    }
}

void read_friendships(FILE *file, List *users_list)
{
    char buffer[MAX_LINE_LENGTH];
    char *token;
    char *saveptr;

    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL)
    {
        token = strtok_r(buffer, ";", &saveptr);
        remove_trailing_character(token, '\n');

        User *user1 = user_find_by_name(users_list, token);
        if (user1 == NULL)
        {
            printf("User %s not found\n", token);
            exit(1);
        }

        token = strtok_r(NULL, ";", &saveptr);
        remove_trailing_character(token, '\n');
        User *user2 = user_find_by_name(users_list, token);
        if (user2 == NULL)
        {
            printf("User %s not found\n", token);
            exit(1);
        }
    }
}

void read_friendship(char *path, List *users_list)
{
    FILE *file = open_file(path, "r");
    read_users(file, users_list);
    read_friendships(file, users_list);
    fclose(file);
}

void read_playlist(List *list, char *playlists_directory, char *playlist_name)
{
    char file_path[MAX_FILE_PATH];
    sprintf(file_path, "%s%s", playlists_directory, playlist_name);
    FILE *file = open_file(file_path, "r");
    char buffer[MAX_LINE_LENGTH];
    char *token;
    char *saveptr;
    char *artist;
    char *song;

    Playlist *playlist = playlist_create(playlist_name);
    list_append(list, playlist);

    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL)
    {
        token = strtok_r(buffer, "-", &saveptr);
        remove_trailing_character(token, ' ');
        artist = token;
        token = strtok_r(NULL, "\n", &saveptr);
        song = token++;
        list_append(playlist_get_songs(playlist), song_create(artist, song));
    }
    fclose(file);
}

void read_playlists(char *playlist_file_path, char* playlists_directory, List *users_list)
{
    FILE *file = open_file(playlist_file_path, "r");
    char buffer[MAX_LINE_LENGTH];
    char *token;
    char *saveptr;

    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL)
    {
        token = strtok_r(buffer, ";", &saveptr);
        User *user = user_find_by_name(users_list, token);
        if (user == NULL)
        {
            printf("User %s not found\n", token);
            exit(1);
        }
        token = strtok_r(NULL, ";", &saveptr); // Discard the number of playlists
        token = strtok_r(NULL, ";", &saveptr);
        while (token != NULL)
        {
            remove_trailing_character(token, '\n');
            read_playlist(user_get_playlists(user), playlists_directory, token);
            token = strtok_r(NULL, ";", &saveptr);
        }
    }
}