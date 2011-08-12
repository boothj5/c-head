#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "card.h"
#include "game.h"
#include "console.h"

static void create_players(Player *players, int nplayers) ;

int main(void)
{
    Game game ;
    
    clearscreen() ;
    show_welcome_msg() ;

    game.num_players = request_num_players() ;
    game.num_cards_each = request_num_cards_each() ;

    newline() ;

    create_deck(&game) ;
    create_players(game.players, game.num_players) ;
    shuffle(&game) ;


    deal(&game) ;

    clearscreen() ;
    show_deck(game.deck_size) ;
    newline() ;
    show_players(game.players, game.num_players) ;
}

static void create_players(Player *players, int nplayers)
{
    int i ;
    char name[MAX_NAME_LEN] ;

    for (i = 0 ; i < nplayers ; i++) {
        request_player_name(name, i+1) ;
        players[i] = make_player(name, HUMAN) ;
    }
}


