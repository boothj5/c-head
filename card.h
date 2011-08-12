#ifndef CARD_H
#define CARD_H

#include <stdlib.h>
#include "game.h"

enum ranks { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
             JACK, QUEEN, KING, ACE } ;

enum suits { HEARTS, SPADES, DIAMONDS, CLUBS } ;

typedef struct {
    int rank ;
    int suit ;
} card ;

char* show_rank(card *c) ;
char* show_suit(card *c) ;
void shuffle(card *deck, size_t n) ;
void create_deck(card *deck, int num_cards) ;

#endif
