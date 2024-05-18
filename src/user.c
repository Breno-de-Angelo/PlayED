#include "list.h"
#include "user.h"
#include "song.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#define CREATE_DIRECTORY(path) CreateDirectory(path, NULL)
#define DIRECTORY_EXISTS_ERROR ERROR_ALREADY_EXISTS
#else
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#define CREATE_DIRECTORY(path) mkdir(path, S_IRWXU)
#define DIRECTORY_EXISTS_ERROR EEXIST
#endif

#define MAX_FILE_PATH   1000


struct User
{
    char *name;
    List *playlists;
    List *friends;
};

struct PlaylistNamePrintConfig
{
    char *separator;
    FILE *file;
};

User *user_create(char *name)
{
    User *user = malloc(sizeof(User));
    user->name = strdup(name);
    user->playlists = list_create();
    user->friends = list_create();
    return user;
}

void user_delete(User *user)
{
    free(user->name);
    list_delete(user->playlists);
    list_delete(user->friends);
    free(user);
}

void *find_user(void *element, void *data)
{
    User *user = (User *) element;
    char *name = (char *) data;
    if (!strcmp(name, user->name))
    {
        return user;
    }
    return NULL;
}

User *list_find_user(List *users_list, char *name)
{
    User *user = (User *) list_iterator(users_list, find_user, name);
    return user;
}

void user_add_friendship(User *user1, User *user2)
{
    list_append(user1->friends, user2);
    list_append(user2->friends, user1);
}

void user_append_playlist(User *user, Playlist *playlist)
{
    list_append(user->playlists, playlist);
}

void *user_update_playlist(void *element, void *data)
{
    User *user = (User *) element;
    (void) data;
    user->playlists = list_playlist_update_by_artist(user->playlists);
    return NULL;
}

void list_user_update_playlist(List *users_list)
{
    // For each user, update playlists to be by artist
    list_iterator(users_list, user_update_playlist, NULL);
}

void *user_name_print(void *element, void *data)
{
    User *user = (User *) element;
    (void) data;
    printf("%s, ", user->name);
    return NULL;
}

void list_user_print(List *list)
{
    printf("[");
    list_iterator(list, user_name_print, NULL);
    printf("\b\b]\n");
}

void *playlists_name_print(void *element, void *data)
{
    Playlist *playlist = (Playlist *) element;
    struct PlaylistNamePrintConfig *config = (struct PlaylistNamePrintConfig *) data;
    fprintf(config->file, "%s%s", playlist_get_name(playlist), config->separator);
    return NULL;
}

void *user_print_playlists(void *element, void *data)
{
    User *user = (User *) element;
    (void) data;
    printf("[");
    struct PlaylistNamePrintConfig config = {
        .separator = ", ",
        .file = stdout
    };
    list_iterator(user->playlists, playlists_name_print, &config);
    printf("\b\b]\n");
    return NULL;
}

void list_user_print_playlists(List *list)
{
    list_iterator(list, user_print_playlists, NULL);
}

void *user_write_played(void *element, void *data)
{
    User *user = (User *) element;
    FILE *file = (FILE *) data;
    list_size(user->playlists);
    fprintf(file, "%s;%d;", user->name, list_size(user->playlists));
    struct PlaylistNamePrintConfig config = {
        .separator = ".txt;",
        .file = file
    };
    list_iterator(user->playlists, playlists_name_print, &config);
    fseek(file, -1, SEEK_CUR);
    fprintf(file, "\n");
    return NULL;
}

void list_user_write_played(List *users_list, char* path)
{
    FILE *file;
    if ((file = fopen(path, "w")) == NULL)
    {
        exit(1);
    }
    list_iterator(users_list, user_write_played, file);
    fclose(file);
}

void *write_playlist(void *element, void *data)
{
    Playlist *playlist = (Playlist *) element;
    char *path = (char *) data;
    char *new_playlist_path = malloc(MAX_FILE_PATH * sizeof(char));
    strcpy(new_playlist_path, path);
    strcat(new_playlist_path, "/");
    strcat(new_playlist_path, playlist_get_name(playlist));
    strcat(new_playlist_path, ".txt");
    FILE *file;
    if ((file = fopen(new_playlist_path, "w")) == NULL)
    {
        exit(1);
    }
    playlist_write_txt(playlist, file);
    fclose(file);
    return NULL;
}

void *user_write_playlist(void *element, void *data)
{
    User *user = (User *) element;
    char *base_path = (char *) data;
    char *path = malloc(MAX_FILE_PATH * sizeof(char));
    strcpy(path, base_path);
    strcat(path, user->name);
    if (mkdir(path, S_IRWXU))
    {
        exit(1);
    }
    list_iterator(user->playlists, write_playlist, path);
    return NULL;
}

void list_user_write_playlists(List *users_list, char* path)
{
    list_iterator(users_list, user_write_playlist, path);
}
