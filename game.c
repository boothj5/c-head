#include "game.h"

int calc_decks_required(int nplayers, int ncards) ;

int cards_required(int nplayers, int ncards)
{
    int decks_required, result ;
    
    decks_required = calc_decks_required(nplayers, ncards) ;
    result = decks_required * DECK_SIZE ;

    return result ;
}


int calc_decks_required(int nplayers, int ncards)
{
    int total_cards, result, div, add ;

    total_cards = nplayers * (ncards * 3) ;
    div = total_cards / DECK_SIZE ;
    add = ((total_cards % DECK_SIZE) > 0) ;
    result = div + add ;

    return result ;
}

