#pragma once
#include "list.h"

typedef struct Song Song;

Song *song_create(char *artist, char *song);
void song_delete(Song *user);