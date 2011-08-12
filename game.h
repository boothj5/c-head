#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "card.h"

#define MAX_NUM_PLAYERS 20
#define MAX_DECK_SIZE 260
#define DECK_SIZE 52

int cards_required(int nplayers, int ncards) ;
void deal(int nplayers, int ncards, player *players, card *deck, int *deck_size) ;

#endif
