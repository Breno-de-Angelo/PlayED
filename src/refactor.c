#include "refactor.h"
#include "user.h"
#include "playlist.h"
#include "song.h"
#include <stdlib.h>
#include <string.h>

Playlist *song_find_by_artist(List *user_playlist, Song *song)
{
    void *prev_playlist = NULL;
    Playlist *playlist = NULL;
    while ((playlist = list_iterate(user_playlist, &prev_playlist)) != NULL)
    {
        if (strcmp(song_get_artist(song), playlist_get_name(playlist)) == 0)
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
                Playlist *playlist_found = song_find_by_artist(user_playlist, song);
                if (playlist_found == NULL)
                {
                    playlist_found = playlist_create(song_get_artist(song));
                    list_append(user_playlist, playlist_found);
                }
                list_append(playlist_get_songs(playlist_found), song);
            }
        }
    }
}