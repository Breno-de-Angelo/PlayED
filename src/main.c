#include "user.h"
#include "txt_io.h"
#include <stdio.h>
#include <string.h>


int main()
{
    List *users_list = list_create();
    char *friendship_file_path = "Facil/Entrada/amizade.txt";
    char *playlists_directory = "Facil/Entrada/";
    char *playlist_file_path = "Facil/Entrada/playlists.txt";
    char *output_refactored_playlists_directory = "Saida/";
    char *output_refactored_list_file_path = "Saida/played-refatorada.txt";
    // char *output_similarity_file_path = "../../Saida/similaridades.txt";

    txt_read_friendship(friendship_file_path, users_list);
    txt_read_playlists(playlist_file_path, playlists_directory, users_list);
    
    #if DEBUG
    printf("User list size: %d\n", list_size(users_list));
    list_user_print(users_list);
    printf("\n");
    printf("Before playlist refactoring.\n");
    list_user_print_playlists(users_list);
    printf("\n");
    #endif
    
    list_user_update_playlist(users_list);
    
    #if DEBUG
    printf("After playlist refactoring.\n");
    list_user_print_playlists(users_list);
    printf("\n");
    #endif
    
    list_user_write_playlists(users_list, output_refactored_playlists_directory);
    list_user_write_played(users_list, output_refactored_list_file_path);
    // list_user_write_similarity(users_list, output_similarity_file_path);
    // txt_write_playlists(users_list);

    return 0;
}
