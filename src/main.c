#include "list.h"
#include "input.h"
#include "refactor.h"
#include "output.h"
#include <stdio.h>
#include <string.h>


int main()
{
    List *users_list = list_create();
    char *friendship_file_path = "Facil/Entrada/amizade.txt";
    char *playlist_file_path = "Facil/Entrada/playlists.txt";
    char *playlists_directory = "Facil/Entrada/";
    // char *output_refactored_list_file_path = "Saida/played-refatorada.txt";
    // char *output_refactored_playlists_directory = "Saida/";
    // char *output_similarity_file_path = "Saida/similaridades.txt";

    read_friendship(friendship_file_path, users_list);
    read_playlists(playlist_file_path, playlists_directory, users_list);
    refactor_playlists(users_list);
    // (users_list);
    // (users_list);
    
    return 0;
}
