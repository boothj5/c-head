#ifndef PLAYER_TYPES_H
#define PLAYER_TYPES_H

#include "player.h"

// human player
int human_ask_swap_cards(struct player_t player);
struct swap_choice_t human_ask_swap_choice(struct player_t player);

// low card player
int lowcardplayer_ask_swap_cards(struct player_t player);
struct swap_choice_t lowcardplayer_ask_swap_choice(struct player_t player);

#endif
