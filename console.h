#ifndef CONSOLE_H
#define CONSOLE_H
     
#include "player.h"
#include "card.h"

void show_welcome_msg();
void newline() ;
void newlines(int) ;
void clearscreen() ;
int request_num_players() ;
int request_num_cards_each() ;
void show_player(player *) ;
void show_players(player *, int) ;
void request_player_name(char *, int) ;
void show_cards(card *, int) ;

#endif
