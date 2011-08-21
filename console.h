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
void show_player(Player p) ;
void show_players(Player *players, int len) ;
void request_player_names(char names[MAX_NUM_PLAYERS][MAX_NAME_LEN], int nplayers) ;
void show_cards(Card *cards, int num_cards) ;
void show_deck(int num_cards) ;

#endif
