#ifndef CONSOLE_H
#define CONSOLE_H
     
#include "player.h"
#include "card.h"

void show_welcome_msg();
void newline() ;
void newlines(int num) ;
void clearscreen() ;
int request_num_players() ;
int request_num_cards_each() ;
void show_player(player *p) ;
void show_players(player *players, int len) ;
void request_player_name(char *name, int num) ;
void show_cards(card *cards, int num_cards) ;

#endif
