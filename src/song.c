#include "song.h"
#include <stdlib.h>
#include <string.h>


struct Song
{
    char *song;
    char *artist;
};


Song *song_create(char *artist, char *song_name)
{
    Song *song = malloc(sizeof(Song));
    song->artist = strdup(artist);
    song->song = strdup(song_name);
    return song;
}

void song_delete(Song *song)
{
    free(song->song);
    free(song->artist);
    free(song);
}
