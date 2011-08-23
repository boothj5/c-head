#include "card.h"

struct card_s make_card(enum cardrank rank, enum cardsuit suit)
{
    struct card_s card ; 
    card.rank = rank ;
    card.suit = suit ;
    return card ;
}

struct card_s lowest(struct card_s *cards, int ncards)
{
    struct card_s lowest = cards[0] ; 
    int i ;
    for (i = 1 ; i < ncards ; i++)
        if (card_cmp(cards[i], lowest) < 0)
            lowest = cards[i] ;
    return lowest ;
}

int special_card(struct card_s c) 
{
    switch(c.rank) {
    case TWO:
        return 1 ;
    case SEVEN:
        return 1 ;
    case TEN:
        return 1 ;
    default:
        return 0 ;
    }
}

int card_cmp(struct card_s c1, struct card_s c2)
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

int equals(struct card_s c1, struct card_s c2) 
{
    return ((c1.rank == c2.rank) && (c1.suit == c2.suit)) ;
}

char* show_rank(struct card_s c)
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

char* show_suit(struct card_s c)
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
