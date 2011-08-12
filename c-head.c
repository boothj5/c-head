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
    
    show_welcome_msg() ;
    game.num_players = request_num_players() ;
    game.num_cards_each = request_num_cards_each() ;
    newline() ;

    calc_cards_required(&game) ;
 
    create_deck(game.deck, game.deck_size) ;

    create_players(game.players, game.num_players) ;

    shuffle(game.deck, game.deck_size) ;
    newline() ;
    printf("Initial deck\n") ;
    show_cards(game.deck, game.deck_size) ;
    newline() ;

    deal(&game) ;

    show_players(game.players, game.num_players) ;
    newline() ;
    printf("Deck after dealing\n") ;
    show_cards(game.deck, game.deck_size) ;
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


