#include "list.h"
#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000


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
        User *user = user_create(token);
        list_append_user(users_list, user);
        token = strtok(NULL, ";");
    }

    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL)
    {
        token = strtok(buffer, ";");
        User *user1 = list_find_user(users_list, token);
        token = strtok(NULL, ";");
        User *user2 = list_find_user(users_list, token);
        user_add_friendship(user1, user2);
    }
    fclose(file);
}

void read_playlists(char *playlist_file_path, char* playlists_directory, User *users_list)
{
    FILE *file;
    if ((file = fopen(playlist_file_path, "r")) == NULL)
    {
        exit(1);
    }

    char buffer[MAX_LINE_LENGTH];
    char *token;
    int num_playlists;
    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL)
    {
        token = strtok(buffer, ";");
        User *user = list_find_user(users_list, token);
        token = strtok(NULL, ";");
        num_playlists = atoi(token);
        token = strtok(NULL, ";");
        while (token != NULL)
        {
            user_add_playlist(user, token, playlists_directory);
        }
    }
    fclose(file);
}

void user_add_playlist(User *user, char *filename, char *playlists_directory)
{
    FILE *file;
    char *file_path;
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
        token = strtok(NULL, ";");
        song = token;
        user_add_song(user, artist, song);
    }
    fclose(file);
}
