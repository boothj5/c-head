#ifndef CARD_H
#define CARD_H

#include <stdlib.h>

enum cardrank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
                JACK, QUEEN, KING, ACE } ;

enum cardsuit { HEARTS, SPADES, DIAMONDS, CLUBS } ;

struct card_s {
    enum cardrank rank ;
    enum cardsuit suit ;
} ;

struct card_s make_card(enum cardrank rank, enum cardsuit suit) ;
struct card_s lowest_card(struct card_s *cards, int ncards) ;
int special_card(struct card_s c) ;

int card_cmp(struct card_s c1, struct card_s c2) ;
int equals(struct card_s c1, struct card_s c2) ;
char* show_rank(struct card_s c) ;
char* show_suit(struct card_s c) ;

#endif
