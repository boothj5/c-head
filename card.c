#include "card.h"
#include "util.h"

struct card_t make_card(enum cardrank rank, enum cardsuit suit)
{
    struct card_t card ; 
    card.rank = rank ;
    card.suit = suit ;
    return card ;
}

struct card_t find_lowest_card(struct card_t *cards, int ncards)
{
    struct card_t lowest = cards[0] ; 
    int i ;
    for (i = 1 ; i < ncards ; i++)
        if (card_cmp(cards[i], lowest) < 0)
            lowest = cards[i] ;
    return lowest ;
}

int special_card(struct card_t c) 
{
    switch(c.rank) {
    case TWO:
        return TRUE ;
    case SEVEN:
        return TRUE ;
    case TEN:
        return TRUE ;
    default:
        return FALSE ;
    }
}

int card_cmp(struct card_t c1, struct card_t c2)
{   
    if (special_card(c1) && special_card(c2))
        return 0 ;
    else if (special_card(c1) && !special_card(c2))
        return 1 ;
    else if (special_card(c2))
        return -1 ;
    else
        return c1.rank - c2.rank ;
}

int equals(struct card_t c1, struct card_t c2) 
{
    return ((c1.rank == c2.rank) && (c1.suit == c2.suit)) ;
}

int ranks_equal(struct card_t c1, struct card_t c2)
{
    return ((c1.rank == c2.rank)) ;
}

int all_ranks_equal(struct card_t *cards, int num_cards) 
{
    struct card_t first_card = cards[0] ;
    int i = 0 ;

    for (i = 1 ; i < num_cards ; i++)
        if (!ranks_equal(cards[i], first_card))
            return FALSE ;

    return TRUE ;
}

char* show_rank(struct card_t c)
{
    switch(c.rank) {
    case TWO:
        return "TWO" ;
    case THREE:
        return "THREE" ;
    case FOUR:
        return "FOUR" ;
    case FIVE:
        return "FIVE" ;
    case SIX:
        return "SIX" ;
    case SEVEN:
        return "SEVEN" ;
    case EIGHT:
        return "EIGHT" ;
    case NINE:
        return "NINE" ;
    case TEN:
        return "TEN" ;
    case JACK:
        return "JACK" ;
    case QUEEN:
        return "QUEEN" ;
    case KING:
        return "KING" ;
    case ACE:
        return "ACE" ;
    default:
        return "ERROR!!!" ;
    }
}

char* show_suit(struct card_t c)
{
    switch(c.suit) {
    case HEARTS:
        return "HEARTS" ;
    case DIAMONDS:
        return "DIAMONDS" ;
    case CLUBS:
        return "CLUBS" ;
    case SPADES:
        return "SPADES" ;
    default:
        return "ERROR!!!!" ;
    } 
}
