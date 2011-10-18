#include "util.h"
#include "card.h"

int burn_cards_laid(struct card_t *pile, int pile_size)
{
    struct card_t cards_on_pile[4] ;
    int num_cards = 0 ;
    int i ;

    if (pile_size > 0) {
        if (pile[pile_size-1].rank == BURN)
            return TRUE ;

        for (i = 0 ; i < 4 ; i++)
            if (pile_size > i) {
                cards_on_pile[i] = pile[pile_size-(i+1)] ;
                num_cards++ ;
            }

        if (num_cards == 4 && all_ranks_equal(cards_on_pile, num_cards))
            return TRUE ;
    }

    return FALSE ;
}

int miss_a_go_card_laid(struct card_t *pile, int pile_size)
{
    if (pile_size > 0)
        if (pile[pile_size-1].rank == MISSAGO)
            return TRUE ;
    return FALSE ;
}

