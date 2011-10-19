#ifndef GAME_RULES_H
#define GAME_RULES_H 

#include "game.h"

int valid_move(struct game_t game, const int card_choices[], const int num_choices) ;
int can_move(const struct game_t game) ;

#endif
