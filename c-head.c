#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "card.h"
#include "game.h"
#include "console.h"

int main(void)
{
    struct game_t game ;
    int nplayers, ncards, i ;
    char names[MAX_NUM_PLAYERS][MAX_NAME_LEN] ;
    
    clearscreen() ;
    show_welcome_msg() ;
    
    nplayers = request_num_players() ;
    ncards = request_num_cards_each() ;
    request_player_names(names, nplayers) ;
    
    game = make_game(nplayers, names, ncards) ;

    for (i = 0 ; i < game.num_players ; i++) {
        clearscreen() ;
        show_player(game.players[i]) ;
        if (request_swap_cards(game.players[i].name))
            printf("YOU WANT TO SWAP\n") ;
        else
            printf("YOU DONT WANT TO SWAP\n") ;
    }

    first_move(&game) ;

    clearscreen() ;
    show_pile(game.pile, game.pile_size) ;
    show_deck(game.deck_size) ;
    show_players(game.players, game.num_players) ;
    show_last_move(game.last_move) ;
}


