#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "card.h"
#include "game.h"
#include "console.h"

int main(void)
{
    struct game_t game ;
    int nplayers, ncards ;
    char names[MAX_NUM_PLAYERS][MAX_NAME_LEN] ;
    
    clearscreen() ;
    show_welcome_msg() ;
    
    nplayers = request_num_players() ;
    ncards = request_num_cards_each() ;
    request_player_names(names, nplayers) ;
    
    game = make_game(nplayers, names, ncards) ;
    first_move(&game) ;

    clearscreen() ;
    show_pile(game.pile, game.pile_size) ;
    show_deck(game.deck_size) ;
    show_players(game.players, game.num_players) ;
    show_last_move(game.last_move) ;
}


