#include "input.h"
#include "user.h"
#include <stdio.h>

#define MAX_LINE_LENGTH 1000

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

void remove_newline(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
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
            remove_newline(token);
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
        remove_newline(token);

        User *user1 = user_find_by_name(users_list, token);
        if (user1 == NULL)
        {
            printf("User %s not found\n", token);
            exit(1);
        }

        token = strtok_r(NULL, ";", &saveptr);
        remove_newline(token);
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

void read_playlists(char *playlist_file_path, char* playlists_directory, List *users_list)
{

}