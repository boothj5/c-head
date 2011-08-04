#include <stdio.h>
#include <stdlib.h>
#include "c-head.h" 

int calc_decks_required(int, int) ;

int main(void)
{
    int num_players, num_cards_each, total_cards_needed, decks_required ;
    player *players ;

    clearscreen() ;
    printf("Welcome to C-Head!") ;
    printf("\n") ;
    printf("\n") ;
    num_players = request_num_players() ;
    num_cards_each = request_num_cards_each() ;
    printf("\n") ;

    decks_required = calc_decks_required(num_players, num_cards_each) ;
    printf("Total decks needed = %d", decks_required) ;
    printf("\n") ;

    players = (player *) malloc(num_players * sizeof(player)) ;

    int i ;
    char name[MAX_NAME_LEN] ;
    for (i = 0 ; i < num_players ; i++) 
    {
        printf("Enter name for player %d :\n", i+1) ;
        scanf("%s", &name) ;
        players[i] = make_player(name, HUMAN) ;
    }
    
    show_players(players, num_players) ;

}

int calc_decks_required(int n_players, int n_cards)
{
    int total_cards, result, div, add ;

    total_cards = n_players * (n_cards * 3) ;
    div = total_cards / 52 ;
    add = ((total_cards % 52) > 0) ;

    result = div + add ;
    return result ;
}


