#pragma once
#include "list.h"

typedef struct Song Song;

Song *song_create(char *artist, char *song);
void song_delete(Song *user);
void song_append_by_artist(void *element, void *data);
char *song_get_artist(Song *song);