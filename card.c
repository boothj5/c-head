#include "card.h"

Card make_card(int rank, int suit)
{
    Card card ;
    card.rank = rank ;
    card.suit = suit ;
    return card ;
}

Card lowest(Card *cards, int ncards)
{
    Card lowest = cards[0] ;
    int i ;

    for (i = 1 ; i < ncards ; i++) 
        if (cards[i].rank < lowest.rank)
            lowest = cards[i] ;
    
    return lowest ;
}

char* show_rank(Card *c)
{
    switch(c->rank) {
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

char* show_suit(Card *c)
{
    switch(c->suit) {
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
