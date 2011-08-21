#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "card.h"

#define MAX_NUM_PLAYERS 20
#define MAX_DECK_SIZE 260
#define DECK_SIZE 52
#define MAX_LAST_MOVE 100

typedef struct game_t *Game ;

Game make_game(int nplayers, char names[MAX_NUM_PLAYERS][MAX_NAME_LEN], int ncards) ;
int deck_size(Game game) ;
int pile_size(Game game) ;
Card *pile(Game game) ;
Player *players(Game game) ;
int num_players(Game game) ;
void first_move(Game game) ;
char *last_move(Game game) ;
#endif
