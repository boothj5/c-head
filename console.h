#ifndef CONSOLE_H
#define CONSOLE_H

#include "player.h"
#include "card.h"
#include "game.h"
    
void show_welcome_msg();
void newline() ;
void newlines(int num) ;
void clearscreen() ;
int request_num_players() ;
int request_num_cards_each() ;
void show_player(struct player_t p) ;
void request_player_names(char names[][MAX_NAME_LEN], int nplayers) ;
void show_cards(struct card_t *cards, int num_cards) ;
void show_game_summary(struct game_t game) ;
int request_swap_cards(char *name) ;
int request_swap_more(char *name) ;
int request_hand_swap(int size) ;
int request_faceup_swap(int size) ;
int request_move(struct player_t player) ;

#endif
