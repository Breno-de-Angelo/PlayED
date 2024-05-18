#include "output.h"
#include "input.h"
#include "user.h"
#include "song.h"
#include "playlist.h"
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


void write_songs(List *songs, FILE *output_file)
{
    void *prev_song = NULL;
    Song *song = NULL;
    while ((song = list_iterate(songs, &prev_song)) != NULL)
    {
        fprintf(output_file, "%s - %s\n", song_get_artist(song), song_get_name(song));
    }
}

void write_playlists(List *users_list, char *output_refactored_playlists_directory)
{
    void *prev_user = NULL;
    User *user = NULL;
    while ((user = list_iterate(users_list, &prev_user)) != NULL)
    {
        char *user_name = user_get_name(user);
        char *output_dir_path = malloc(MAX_FILE_PATH);
        sprintf(output_dir_path, "%s%s", output_refactored_playlists_directory, user_name);
        if (mkdir(output_dir_path, S_IRWXU))
        {
            exit(1);
        }

        List *playlists = user_get_playlists(user);
        void *prev_playlist = NULL;
        Playlist *playlist = NULL;
        char *output_file_path = malloc(MAX_FILE_PATH);
        while ((playlist = list_iterate(playlists, &prev_playlist)) != NULL)
        {
            char *playlist_name = playlist_get_name(playlist);
            sprintf(output_file_path, "%s/%s.txt", output_dir_path, playlist_name);
            FILE *output_file = open_file(output_file_path, "w");
            write_songs(playlist_get_songs(playlist), output_file);
            fclose(output_file);
        }
    }
}

void write_summary(List *users_list, char *output_summary_file_path)
{
    FILE *output_file = open_file(output_summary_file_path, "w");
    void *prev_user = NULL;
    User *user = NULL;
    while ((user = list_iterate(users_list, &prev_user)) != NULL)
    {
        List *playlists = user_get_playlists(user);
        fprintf(output_file, "%s;%d", user_get_name(user), list_size(playlists));
        void *prev_playlist = NULL;
        Playlist *playlist = NULL;
        while ((playlist = list_iterate(playlists, &prev_playlist)) != NULL)
        {
            fprintf(output_file, ";%s.txt", playlist_get_name(playlist));
        }
        fprintf(output_file, "\n");
    }
    fclose(output_file);
}

int compare_songs(Playlist *user_playlist, Playlist *friend_playlist)
{
    int similar_songs = 0;
    List *user_songs = playlist_get_songs(user_playlist);
    List *friend_songs = playlist_get_songs(friend_playlist);
    void *prev_user_song = NULL;
    Song *user_song = NULL;
    while ((user_song = list_iterate(user_songs, &prev_user_song)) != NULL)
    {
        void *prev_friend_song = NULL;
        Song *friend_song = NULL;
        while ((friend_song = list_iterate(friend_songs, &prev_friend_song)) != NULL)
        {
            if (!strcmp(song_get_name(user_song), song_get_name(friend_song)))
            {
                similar_songs++;
            }
        }
    }
    return similar_songs;
}

int compare_playlists(User *user, User *friend)
{
    List *user_playlists = user_get_playlists(user);
    List *friend_playlists = user_get_playlists(friend);
    int similar_songs = 0;
    void *prev_user_playlist = NULL;
    Playlist *user_playlist = NULL;
    while ((user_playlist = list_iterate(user_playlists, &prev_user_playlist)) != NULL)
    {
        void *prev_friend_playlist = NULL;
        Playlist *friend_playlist = NULL;
        while ((friend_playlist = list_iterate(friend_playlists, &prev_friend_playlist)) != NULL)
        {
            if (strcmp(playlist_get_name(user_playlist), playlist_get_name(friend_playlist)) != 0)
            {
                continue;
            }
            similar_songs += compare_songs(user_playlist, friend_playlist);
        }
    }
    return similar_songs;
}

void write_similarity(List *users_list, char *output_similarity_file_path)
{
    FILE *output_file = open_file(output_similarity_file_path, "w");
    List *visited_users = list_create();
    void *prev_user = NULL;
    User *user = NULL;
    while ((user = list_iterate(users_list, &prev_user)) != NULL)
    {
        List *friends = user_get_friends(user);
        void *prev_friend = NULL;
        User *friend = NULL;
        while ((friend = list_iterate(friends, &prev_friend)) != NULL)
        {
            if (user_find_by_name(visited_users, user_get_name(friend)) == NULL)
            {
                fprintf(output_file, "%s;%s;%d\n", user_get_name(user), user_get_name(friend), compare_playlists(user, friend));
            }
        }
        list_append(visited_users, user);
    }
    fclose(output_file);
}