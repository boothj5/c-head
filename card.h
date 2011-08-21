#ifndef CARD_H
#define CARD_H

#include <stdlib.h>

enum cardrank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
                JACK, QUEEN, KING, ACE } ;

enum cardsuit { HEARTS, SPADES, DIAMONDS, CLUBS } ;

typedef struct card_t *Card ;

Card make_card(enum cardrank rank, enum cardsuit suit) ;
enum cardrank rank(Card c) ;
Card lowest(Card *cards, int ncards) ;
int special_card(Card card) ;
int card_cmp(Card c1, Card c2) ;
char* show_rank(Card c) ;
char* show_suit(Card c) ;

#endif
