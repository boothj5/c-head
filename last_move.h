#ifndef LAST_MOVE_H
#define LAST_MOVE_H

#include "card.h"

void set_last_move(char *last_move, char *name, struct card_t *cards, int ncards) ;
void set_last_move_was_burn(char *last_move, char *name) ;
void set_last_move_pickup(char *last_move, char *name) ;
void set_last_move_was_miss_a_go(char *last_move, char *name) ;
#endif
