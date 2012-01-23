#ifndef LAST_MOVE_H
#define LAST_MOVE_H

#include "card.h"

void set_last_move(char *last_move, const char *name, const struct card_t *cards, 
    const int num_cards);
void set_last_move_was_burn(char *last_move, const char *name);
void set_last_move_pickup(char *last_move, const char *name);
void set_last_move_was_miss_a_go(char *last_move, const char *name);

#endif
