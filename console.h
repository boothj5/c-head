#ifndef CONSOLE_H
#define CONSOLE_H

#include "player.h"
#include "card.h"
#include "game.h"
    
void show_welcome_msg();
void newline() ;
void newlines(const int num) ;
void clearscreen() ;
int request_num_players() ;
int request_num_cards_each() ;
void show_player(const struct player_t p) ;
void request_player_names(char names[][MAX_NAME_LEN], const int nplayers) ;
void show_cards(const struct card_t *cards, const int num_cards) ;
void show_game_summary(const struct game_t game) ;
int request_swap_cards(const char *name) ;
int request_swap_more(const char *name) ;
int request_hand_swap(const int size) ;
int request_faceup_swap(const int size) ;
void request_move(const struct player_t player, int card_choices[], int *num_choices) ;
void show_shithead(const struct player_t player) ;
void wait_user() ;
void show_bad_move() ;
void show_pickup(const char *name) ;

#endif
