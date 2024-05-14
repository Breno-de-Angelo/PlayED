#include "user.h"
#include <stdio.h>
#include <string.h>


int main()
{
    List *users_list = list_create();
    char *friendship_file_path = "/home/breno/ufes/PlayED/Facil/Entrada/amizade.txt";
    char *playlists_directory = "/home/breno/ufes/PlayED/Facil/Entrada/";
    char *playlist_file_path = "/home/breno/ufes/PlayED/Facil/Entrada/playlists.txt";

    read_friendship(friendship_file_path, users_list);
    read_playlists(playlist_file_path, playlists_directory, users_list);
    return 0;
}
