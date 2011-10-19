#ifndef CARD_H
#define CARD_H

#include <stdlib.h>

#define INVISIBLE 7
#define RESET     2
#define BURN      10
#define MISSAGO    8

enum cardrank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
                JACK, QUEEN, KING, ACE } ;

enum cardsuit { HEARTS, SPADES, DIAMONDS, CLUBS } ;

struct card_t {
    enum cardrank rank ;
    enum cardsuit suit ;
} ;

struct card_t make_card(enum cardrank rank, enum cardsuit suit) ;
struct card_t find_lowest_card(struct card_t *cards, int ncards) ;
int special_card(struct card_t c) ;

int card_cmp(struct card_t c1, struct card_t c2) ;
int cards_equal(struct card_t c1, struct card_t c2) ;
int ranks_equal(struct card_t c1, struct card_t c2) ;
int all_ranks_equal(struct card_t *cards, int num_cards) ; 
char* show_rank(struct card_t c) ;
char* show_suit(struct card_t c) ;

#endif
