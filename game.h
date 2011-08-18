#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "card.h"

#define MAX_NUM_PLAYERS 20
#define MAX_DECK_SIZE 260
#define DECK_SIZE 52

typedef struct {
    int num_players ;
    int num_cards_each ;
    int deck_size ;
    Player players[MAX_NUM_PLAYERS] ;
    Card deck[MAX_DECK_SIZE] ;
} Game ;

void init(Game *game, int nplayers, char names[MAX_NUM_PLAYERS][MAX_NAME_LEN], int ncards) ;
void create_deck(Game *game) ;
void deal(Game *game) ;
void shuffle(Game *game) ;

#endif
