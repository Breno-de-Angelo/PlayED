#include "list.h"
#include "input.h"
#include "playlist_operations.h"
#include "output.h"
#include <stdio.h>
#include <string.h>


int main()
{
    List *users_list = list_create();
    char *friendship_file_path = "Facil/Entrada/amizade.txt";
    char *playlist_file_path = "Facil/Entrada/playlists.txt";
    char *playlists_directory = "Facil/Entrada/";
    char *output_refactored_playlists_directory = "Saida/";
    char *output_summary_file_path = "Saida/played-refatorada.txt";
    char *output_similarity_file_path = "Saida/similaridades.txt";
    char *output_merged_playlists_directory = "Saida/merged/";

    create_directory(output_refactored_playlists_directory);
    create_directory(output_merged_playlists_directory);
    read_friendship(friendship_file_path, users_list);
    read_playlists(playlist_file_path, playlists_directory, users_list);
    refactor_playlists(users_list);
    write_playlists(users_list, output_refactored_playlists_directory);
    write_summary(users_list, output_summary_file_path);
    write_similarity(users_list, output_similarity_file_path);
    // merge_playlists(users_list);
    // write_playlists(users_list, output_merged_playlists_directory);

    list_destroy(users_list);
    
    return 0;
}
