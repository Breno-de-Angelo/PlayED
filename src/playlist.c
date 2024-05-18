#include "playlist.h"
#include <stdlib.h>
#include <string.h>


struct Playlist
{
    char *name;
    List *songs;
};

char *playlist_get_name(Playlist *playlist)
{
    return playlist->name;
}

List *playlist_get_songs(Playlist *playlist)
{
    return playlist->songs;
}

Playlist *playlist_create(char *name)
{
    Playlist *playlist = malloc(sizeof(Playlist));
    playlist->name = strdup(name);
    playlist->songs = list_create();
    return playlist;
}

void playlist_delete(Playlist *playlist)
{
    free(playlist->name);
    list_delete(playlist->songs);
    free(playlist);
}