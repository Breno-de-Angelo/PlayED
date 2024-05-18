#pragma once
#include "list.h"

typedef struct Playlist Playlist;

char *playlist_get_name(Playlist *playlist);
List *playlist_get_songs(Playlist *playlist);
Playlist *playlist_create(char *name);




void playlist_append_song(Playlist *playlist, Song *song);
List *list_playlist_update_by_artist(List *list);
void playlist_write_txt(Playlist *playlist, FILE *file);
