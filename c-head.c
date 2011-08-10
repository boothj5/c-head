#include <stdio.h>
#include <stdlib.h>
#include "c-head.h" 

void create_players(player **, int) ;
void populate_players(player *, int) ;

int main(void)
{
    int num_players, num_cards_each, total_cards_needed, decks_required ;
    player *players ;
    card *deck ;

    clearscreen() ;
    show_welcome_msg() ;
    num_players = request_num_players() ;
    num_cards_each = request_num_cards_each() ;
    newline() ;

    decks_required = calc_decks_required(num_players, num_cards_each) ;
    total_cards_needed = cards_required(decks_required) ;

    create_players(&players, num_players) ;

    deck = (card *) malloc(total_cards_needed * sizeof(card)) ;
    create_deck(deck, decks_required) ;

    show_players(players, num_players) ;
    show_deck(deck, total_cards_needed) ;
}

void create_players(player **players, int num_players)
{
    *players = (player *) malloc(num_players * sizeof(player)) ;
    populate_players(*players, num_players) ;
}

void populate_players(player *players, int num_players)
{
    int i ;
    char name[MAX_NAME_LEN] ;

    for (i = 0 ; i < num_players ; i++) 
    {
        request_player_name(name, i+1) ;
        players[i] = make_player(name, HUMAN) ;
    }
}
