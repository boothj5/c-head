#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "card.h"
#include "game.h"
#include "console.h"

int main(void)
{
    Game game ;
    int num_players, num_cards_each ;
    char names[MAX_NUM_PLAYERS][MAX_NAME_LEN] ;
    
    clearscreen() ;
    show_welcome_msg() ;

    num_players = request_num_players() ;
    num_cards_each = request_num_cards_each() ;
    request_player_names(names, num_players) ;

    newline() ;

    init(&game, num_players, names, num_cards_each) ;
    create_deck(&game) ;
    shuffle(&game) ;
    deal(&game) ;

    clearscreen() ;
    show_deck(game.deck_size) ;
    newline() ;
    show_players(game.players, game.num_players) ;
}


