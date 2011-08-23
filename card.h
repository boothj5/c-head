#ifndef CARD_H
#define CARD_H

#include <stdlib.h>

enum cardrank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
                JACK, QUEEN, KING, ACE } ;

enum cardsuit { HEARTS, SPADES, DIAMONDS, CLUBS } ;

struct card_t {
    enum cardrank rank ;
    enum cardsuit suit ;
} ;

struct card_t make_card(enum cardrank rank, enum cardsuit suit) ;
struct card_t lowest_card(struct card_t *cards, int ncards) ;
int special_card(struct card_t c) ;

int card_cmp(struct card_t c1, struct card_t c2) ;
int equals(struct card_t c1, struct card_t c2) ;
char* show_rank(struct card_t c) ;
char* show_suit(struct card_t c) ;

#endif
