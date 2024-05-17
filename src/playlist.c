#include "playlist.h"
#include <stdlib.h>
#include <string.h>

struct Playlist
{
    char *name;
    List *songs;
};

Playlist *playlist_create(char *name)
{
    Playlist *playlist = malloc(sizeof(Playlist));
    playlist->name = strdup(name);
    playlist->songs = list_create();
    return playlist;
}

void playlist_append_song(Playlist *playlist, Song *song)
{
    list_append(playlist->songs, song);
}

void *playlist_find_artist(void *element, void *data)
{
    Playlist *playlist = (Playlist *) element;
    char *artist = (char *) data;
    if (!strcmp(playlist->name, artist))
    {
        return playlist;
    }
    return NULL;
}

void *list_playlists_append_song(void *element, void *data)
{
    Song *song = (Song *) element;
    List *new_list = (List *) data;
    char *artist = song_get_artist(song);
    Playlist *playlist_found = (Playlist *) list_iterator(new_list, playlist_find_artist, artist);
    if (!playlist_found)
    {
        Playlist *new_playlist = playlist_create(artist);
        list_append(new_list, new_playlist);
    }
    else
    {
        list_append(playlist_found->songs, song);
    }
    return NULL;
}

void *playlist_update_by_artist(void *element, void *data)
{
    Playlist *playlist = (Playlist *) element;
    List *new_list = (List *) data;
    list_iterator(playlist->songs, list_playlists_append_song, new_list);
    return NULL;
}

void *list_playlists_delete(void *element, void *data)
{
    Playlist *playlist = (Playlist *) element;
    (void) data;
    free(playlist->name);
    free(playlist);
    return NULL;
}

List *list_playlist_update_by_artist(List *list)
{
    List *new_list = list_create();
    list_iterator(list, playlist_update_by_artist, new_list);
    list_iterator(list, list_playlists_delete, NULL);
    return new_list;
}
