#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "card.h"

#define MAX_NUM_PLAYERS 20
#define MAX_DECK_SIZE 260
#define DECK_SIZE 52
#define MAX_LAST_MOVE 100

struct game_t {
    int num_players ;
    int num_cards_each ;
    int deck_size ;
    int pile_size ;
    struct player_t players[MAX_NUM_PLAYERS] ;
    struct card_t deck[MAX_DECK_SIZE] ;
    struct card_t pile[MAX_DECK_SIZE] ;
    char last_move[MAX_LAST_MOVE] ;
} ;

struct game_t *make_game(int nplayers, char names[MAX_NUM_PLAYERS][MAX_NAME_LEN], int ncards) ;
void first_move(struct game_t *game) ;

#endif
