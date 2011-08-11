#include "c-head.h"

int calc_decks_required(int, int) ;

int cards_required(int n_players, int n_cards)
{
    int decks_required, result ;
    
    decks_required = calc_decks_required(n_players, n_cards) ;
    result = decks_required * DECK_SIZE ;

    return result ;
}


int calc_decks_required(int n_players, int n_cards)
{
    int total_cards, result, div, add ;

    total_cards = n_players * (n_cards * 3) ;
    div = total_cards / DECK_SIZE ;
    add = ((total_cards % DECK_SIZE) > 0) ;
    result = div + add ;

    return result ;
}



