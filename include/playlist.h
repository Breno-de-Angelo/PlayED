#pragma once

#include "list.h"
#include "song.h"
#include <stdio.h>

typedef struct Playlist Playlist;

Playlist *playlist_create(char *name);
void playlist_append_song(Playlist *playlist, Song *song);
List *list_playlist_update_by_artist(List *list);
char *playlist_get_name(Playlist *playlist);
void playlist_write_txt(Playlist *playlist, FILE *file);
