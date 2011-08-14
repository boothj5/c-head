#ifndef CARD_H
#define CARD_H

#include <stdlib.h>

enum ranks { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
             JACK, QUEEN, KING, ACE } ;

enum suits { HEARTS, SPADES, DIAMONDS, CLUBS } ;

typedef struct {
    int rank ;
    int suit ;
} Card ;

Card make_card(int rank, int suit) ;
Card lowest(Card *cards, int ncards) ;
char* show_rank(Card *c) ;
char* show_suit(Card *c) ;

#endif
