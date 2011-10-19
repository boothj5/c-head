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
    int burnt_size ;
    struct player_t players[MAX_NUM_PLAYERS] ;
    int current_player ;
    struct card_t deck[MAX_DECK_SIZE] ;
    struct card_t pile[MAX_DECK_SIZE] ;
    struct card_t burnt[MAX_DECK_SIZE] ;
    char last_move[MAX_LAST_MOVE] ;
    int miss_a_go ;
} ;

struct game_t make_game(int num_players, char names[][MAX_NAME_LEN], int num_cards) ;
void init_game(struct game_t *game) ;
void first_move(struct game_t *game) ;
void make_move(struct game_t *game, int card_choices[], int num_choices) ;
int continue_play(struct game_t game) ;
int valid_move(struct game_t game, int card_choices[], int num_choices) ;
int can_move(struct game_t game) ;
struct player_t get_shithead(struct game_t game) ;
void pick_up_pile(struct game_t *game) ;
void move_to_next_player(struct game_t *game) ;

#endif
