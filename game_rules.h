#ifndef GAME_RULES_H
#define GAME_RULES_H 

#include "game.h"

int valid_move(struct game_t game, const int card_choices[], const int num_choices) ;
int can_move(const struct game_t game) ;
int can_lay_from_face_down(const struct game_t game, const int choice) ;
int can_lay(const struct card_t card, const struct card_t *pile, const int pile_size);

#endif
