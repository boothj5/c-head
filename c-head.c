#include <stdio.h>
#include <stdlib.h>
#include "c-head.h" 

void create_players(player *, int) ;

int main(void)
{
    int i, num_players, num_cards_each, total_cards_needed, decks_required ;
    player *players ;
    card *deck ;

    clearscreen() ;
    show_welcome_msg() ;
    num_players = request_num_players() ;
    num_cards_each = request_num_cards_each() ;
    newline() ;

    decks_required = calc_decks_required(num_players, num_cards_each) ;
    total_cards_needed = decks_required * 52 ;

    players = (player *) malloc(num_players * sizeof(player)) ;
   
    create_players(players, num_players) ;
    show_players(players, num_players) ;

    deck = (card *) malloc(total_cards_needed * sizeof(card)) ;
    create_deck(deck, decks_required) ;

    for (i = 0 ; i < total_cards_needed ; i++)
    {
        printf("Num: %d, Rank: %d, Suit: %d\n", i, deck[i].rank, deck[i].suit) ;
    }

}

void create_players(player *players, int num_players)
{
    int i ;
    char name[MAX_NAME_LEN] ;

    for (i = 0 ; i < num_players ; i++) 
    {
        request_player_name(name, i+1) ;
        players[i] = make_player(name, HUMAN) ;
    }
}
