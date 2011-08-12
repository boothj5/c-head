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

char* show_rank(card *) ;
char* show_suit(card *) ;
void shuffle(card *, size_t) ;
void create_deck(card *, int) ;

#endif
