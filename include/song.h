#pragma once
#include "list.h"

typedef struct Song Song;

Song *song_create(char *nome);
void song_delete(Song *user);
void list_append_song(List *list, Song *data);