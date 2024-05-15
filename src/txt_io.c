#include "list.h"
#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define MAX_FILE_PATH   1000

void read_friendship(char *path, List *users_list)
{
    FILE *file;
    if ((file = fopen(path, "r")) == NULL)
    {
        exit(1);
    }

    char buffer[MAX_LINE_LENGTH];
    fgets(buffer, MAX_LINE_LENGTH, file);
    
    char *token;
    token = strtok(buffer, ";");
    while (token != NULL)
    {
        if (token[strlen(token) - 1] == '\n')
        {
            token[strlen(token) - 1] = '\0';
        }
        User *user = user_create(token);
        list_append(users_list, user);
        token = strtok(NULL, ";");
    }

    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL)
    {
        token = strtok(buffer, ";");
        User *user1 = list_find_user(users_list, token);
        token = strtok(NULL, ";");
        token[strlen(token) - 1] = '\0';
        User *user2 = list_find_user(users_list, token);
        user_add_friendship(user1, user2);
    }
    fclose(file);
}

void read_playlist(User *user, char *filename, char *playlists_directory)
{
    FILE *file;
    char *file_path = malloc(MAX_FILE_PATH * sizeof(char));
    strcpy(file_path, playlists_directory);
    strcat(file_path, filename);
    if ((file = fopen(file_path, "r")) == NULL)
    {
        exit(1);
    }

    char buffer[MAX_LINE_LENGTH];
    char *token;
    char *artist;
    char *song;
    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL)
    {
        token = strtok(buffer, "-");
        artist = token;
        token = strtok(NULL, "\n");
        song = token;
        user_add_song(user, artist, song);
    }
    fclose(file);
}

void read_playlists(char *playlist_file_path, char* playlists_directory, List *users_list)
{
    FILE *file;
    if ((file = fopen(playlist_file_path, "r")) == NULL)
    {
        exit(1);
    }

    char buffer[MAX_LINE_LENGTH];
    char *token;
    // int num_playlists;
    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL)
    {
        token = strtok(buffer, ";");
        User *user = list_find_user(users_list, token);
        token = strtok(NULL, ";");
        // num_playlists = atoi(token);
        token = strtok(NULL, ";");
        while (token != NULL)
        {
            read_playlist(user, token, playlists_directory);
        }
    }
    fclose(file);
}
