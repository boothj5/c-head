#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "card.h"
#include "game.h"
#include "console.h"

int main(void)
{
    Game game ;
    int nplayers, ncards ;
    char names[MAX_NUM_PLAYERS][MAX_NAME_LEN] ;
    
    clearscreen() ;
    show_welcome_msg() ;
    
    nplayers = request_num_players() ;
    ncards = request_num_cards_each() ;
    request_player_names(names, nplayers) ;
    
    game = make_game(nplayers, names, ncards) ;
    first_move(game) ;

    clearscreen() ;
    show_pile(pile(game), pile_size(game)) ;
    show_deck(deck_size(game)) ;
    show_players(players(game), num_players(game)) ;
    show_last_move(last_move(game)) ;
}


