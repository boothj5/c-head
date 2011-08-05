#include "c-head.h"

int calc_decks_required(int n_players, int n_cards)
{
    int total_cards, result, div, add ;

    total_cards = n_players * (n_cards * 3) ;
    div = total_cards / 52 ;
    add = ((total_cards % 52) > 0) ;

    result = div + add ;
    return result ;
}

