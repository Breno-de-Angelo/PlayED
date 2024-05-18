#pragma once
#include "list.h"

typedef struct Playlist Playlist;

char *playlist_get_name(Playlist *playlist);
List *playlist_get_songs(Playlist *playlist);
Playlist *playlist_create(char *name);