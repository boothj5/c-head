#ifndef PLAYER_TYPES_H
#define PLAYER_TYPES_H

#include "player.h"

// human player
int human_ask_swap_cards(const struct player_t player);
struct swap_choice_t human_ask_swap_choice(const struct player_t player);
void human_ask_move(const struct player_t player,
    const struct player_helper_t helper, int card_choices[], int *nchoices);
int human_ask_face_down_move(void);

// low card player
int lowcardplayer_ask_swap_cards(const struct player_t player);
struct swap_choice_t lowcardplayer_ask_swap_choice(const struct player_t player);
void lowcardplayer_ask_move(const struct player_t player,
    const struct player_helper_t helper, int card_choices[], int *nchoices);
int lowcardplayer_ask_face_down_move(void);

#endif
