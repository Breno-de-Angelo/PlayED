#include "playlist_operations.h"
#include "user.h"
#include "playlist.h"
#include "song.h"
#include <stdlib.h>
#include <string.h>

Playlist *song_find_by_artist(List *user_playlist, char *artist)
{
    void *prev_playlist = NULL;
    Playlist *playlist = NULL;
    while ((playlist = list_iterate(user_playlist, &prev_playlist)) != NULL)
    {
        if (strcmp(artist, playlist_get_name(playlist)) == 0)
        {
            break;
        }
    }
    return playlist;
}

void refactor_playlists(List *users_list)
{
    void *prev_user = NULL;
    User *user = NULL;
    while ((user = list_iterate(users_list, &prev_user)) != NULL)
    {
        List *user_playlist = list_create();
        
        List *playlists = user_get_playlists(user);
        void *prev_playlist = NULL;
        Playlist *playlist = NULL;
        while ((playlist = list_iterate(playlists, &prev_playlist)) != NULL)
        {
            List *songs = playlist_get_songs(playlist);
            void *prev_song = NULL;
            Song *song = NULL;
            while ((song = list_iterate(songs, &prev_song)) != NULL)
            {
                Playlist *playlist_found = song_find_by_artist(user_playlist, song_get_artist(song));
                if (playlist_found == NULL)
                {
                    playlist_found = playlist_create(song_get_artist(song));
                    list_append(user_playlist, playlist_found);
                }
                list_append(playlist_get_songs(playlist_found), song);
            }
        }
        void *prev_playlist_old = NULL;
        Playlist *playlist_old = NULL;
        while ((playlist_old = list_iterate(user_get_playlists(user), &prev_playlist_old)) != NULL)
        {
            playlist_delete(playlist_old);
        }
        user_set_playlist(user, user_playlist);
    }
}

void traverse_graph(User *user, List *visited_users)
{
    list_append(visited_users, user);
    List *user_friends = user_get_friends(user);
    void *prev_friend = NULL;
    User *neighbor = NULL;
    while ((neighbor = list_iterate(user_friends, &prev_friend)) != NULL)
    {
        if (user_find_by_name(visited_users, user_get_name(neighbor)) == NULL)
        {
            traverse_graph(neighbor, visited_users);
        }
    }
}

void append_visited_users_to_list(List *visited_users, List *new_visited_users)
{
    void *prev_user = NULL;
    User *user = NULL;
    while ((user = list_iterate(new_visited_users, &prev_user)) != NULL)
    {
        list_append(visited_users, user);
    }
}

List *get_disjoint_graphs(List *users_list)
{
    List *disjoint_graphs = list_create();
    List *visited_users = list_create();

    void *prev_user = NULL;
    User *user = NULL;
    while ((user = list_iterate(users_list, &prev_user)) != NULL)
    {
        if (user_find_by_name(visited_users, user_get_name(user)) == NULL)
        {
            List *new_visited_users = list_create();
            traverse_graph(user, new_visited_users);
            list_append(disjoint_graphs, new_visited_users);
            append_visited_users_to_list(visited_users, new_visited_users);
        }
    }

    list_delete(visited_users);
    return disjoint_graphs;    
}

Song *song_find_by_name(List *playlist, Song *song)
{
    void *prev_song = NULL;
    Song *song_found = NULL;
    while ((song_found = list_iterate(playlist, &prev_song)) != NULL)
    {
        if (strcmp(song_get_name(song_found), song_get_name(song)) == 0)
        {
            break;
        }
    }
    return song_found;
}

void merge_playlists_in_graph(List *graph)
{
    List *merged_playlists = list_create();
    void *prev_user = NULL;
    User *user = NULL;
    while ((user = list_iterate(graph, &prev_user)) != NULL)
    {
        List *user_playlists = user_get_playlists(user);
        void *prev_playlist = NULL;
        Playlist *playlist = NULL;
        while ((playlist = list_iterate(user_playlists, &prev_playlist)) != NULL)
        {
            Playlist *playlist_found = song_find_by_artist(merged_playlists, playlist_get_name(playlist));
            if (playlist_found == NULL)
            {
                playlist_found = playlist_create(playlist_get_name(playlist));
                list_append(merged_playlists, playlist_found);
            }
            List *songs = playlist_get_songs(playlist);
            void *prev_song = NULL;
            Song *song = NULL;
            while ((song = list_iterate(songs, &prev_song)) != NULL)
            {
                if (song_find_by_name(playlist_get_songs(playlist_found), song) != NULL)
                {
                    continue;
                }
                list_append(playlist_get_songs(playlist_found), song);
            }
        }
    }

    prev_user = NULL;
    user = NULL;
    while ((user = list_iterate(graph, &prev_user)) != NULL)
    {
        void *prev_playlist = NULL;
        Playlist *playlist = NULL;
        while ((playlist = list_iterate(merged_playlists, &prev_playlist)) != NULL)
        {
            Playlist *playlist_found = song_find_by_artist(merged_playlists, playlist_get_name(playlist));
            if (playlist_found != NULL)
            {
                list_remove(user_get_playlists(user), playlist);
                list_append(user_get_playlists(user), playlist_found);
            }
        }
    }
}

void merge_playlists(List *users_list)
{
    List *disjoint_graphs = get_disjoint_graphs(users_list);
    void *prev_graph = NULL;
    List *graph = NULL;
    while ((graph = list_iterate(disjoint_graphs, &prev_graph)) != NULL)
    {
        merge_playlists_in_graph(graph);
    }
    list_delete(disjoint_graphs);
}

void list_destroy(List *users_list)
{
    void *prev_user = NULL;
    User *user = NULL;
    while ((user = list_iterate(users_list, &prev_user)) != NULL)
    {
        void *prev_playlist = NULL;
        Playlist *playlist = NULL;
        List *playlists = user_get_playlists(user);
        while ((playlist = list_iterate(playlists, &prev_playlist)) != NULL)
        {
            void *prev_song = NULL;
            Song *song = NULL;
            List *songs = playlist_get_songs(playlist);
            while ((song = list_iterate(songs, &prev_song)) != NULL)
            {
                song_delete(song);
            }
            playlist_delete(playlist);
        }
        user_delete(user);
    }
    list_delete(users_list);
}
