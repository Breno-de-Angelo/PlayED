#include "list.h"
#include "user.h"
#include "song.h"
#include "playlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define MAX_FILE_PATH   1000

void txt_read_friendship(char *path, List *users_list)
{
    FILE *file;
    if ((file = fopen(path, "r")) == NULL)
    {
        exit(1);
    }

    char buffer[MAX_LINE_LENGTH];
    char *token;
    char *saveptr;

    if (fgets(buffer, MAX_LINE_LENGTH, file) != NULL)
    {
        token = strtok_r(buffer, ";", &saveptr);
        while (token != NULL)
        {
            size_t len = strlen(token);
            if (len > 0 && token[len - 1] == '\n')
            {
                token[len - 1] = '\0';
            }
            User *user = user_create(token);
            list_append(users_list, user);
            token = strtok_r(NULL, ";", &saveptr);
        }
    }

    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL)
    {
        token = strtok_r(buffer, ";", &saveptr);
        if (token != NULL)
        {
            size_t len = strlen(token);
            if (len > 0 && token[len - 1] == '\n')
            {
                token[len - 1] = '\0';
            }
            User *user1 = list_find_user(users_list, token);

            token = strtok_r(NULL, ";", &saveptr);
            if (token != NULL)
            {
                len = strlen(token);
                if (len > 0 && token[len - 1] == '\n')
                {
                    token[len - 1] = '\0';
                }
                User *user2 = list_find_user(users_list, token);
                user_add_friendship(user1, user2);
            }
        }
    }
    fclose(file);
}

void read_playlist(User *user, char *playlist_name, char *playlists_directory)
{
    FILE *file;
    char *file_path = malloc(MAX_FILE_PATH * sizeof(char));
    strcpy(file_path, playlists_directory);
    strcat(file_path, playlist_name);

    if ((file = fopen(file_path, "r")) == NULL)
    {
        exit(1);
    }

    Playlist *playlist = playlist_create(playlist_name);

    char buffer[MAX_LINE_LENGTH];
    char *token;
    char *artist;
    char *song_name;
    char *saveptr;

    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL)
    {
        token = strtok_r(buffer, "-", &saveptr);
        if (token != NULL)
        {
            artist = token;
            size_t len = strlen(artist);
            artist[len - 1] = '\0';
            token = strtok_r(NULL, "\n", &saveptr);
            if (token != NULL)
            {
                song_name = token;
                song_name += 1;
                Song *song = song_create(artist, song_name);
                playlist_append_song(playlist, song);
            }
        }
    }
    user_append_playlist(user, playlist);
    fclose(file);
    free(file_path);
}

void txt_read_playlists(char *playlist_file_path, char* playlists_directory, List *users_list)
{
    FILE *file;
    if ((file = fopen(playlist_file_path, "r")) == NULL)
    {
        exit(1);
    }

    char buffer[MAX_LINE_LENGTH];
    char *token;
    char *saveptr1;
    char *saveptr2;

    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL)
    {
        token = strtok_r(buffer, ";", &saveptr1);
        if (token != NULL)
        {
            User *user = list_find_user(users_list, token);
            if (user == NULL)
            {
                exit(1);
            }
            token = strtok_r(NULL, ";", &saveptr1);
            // int num_playlists = atoi(token);
            token = strtok_r(NULL, ";", &saveptr1);
            while (token != NULL)
            {
                char *playlist_name = strtok_r(token, "\n", &saveptr2);
                if (playlist_name != NULL)
                {
                    read_playlist(user, playlist_name, playlists_directory);
                }
                token = strtok_r(NULL, ";", &saveptr1);
            }
        }
    }
    fclose(file);
}