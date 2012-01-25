#ifndef PLAYER_TYPES_H
#define PLAYER_TYPES_H

#include "player.h"
#include "config.h"

struct player_type_t {
    char type;
    char name[MAX_NAME_LEN];
};

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

// random card player
int randomcardplayer_ask_swap_cards(const struct player_t player);
struct swap_choice_t randomcardplayer_ask_swap_choice(const struct player_t player);
void randomcardplayer_ask_move(const struct player_t player,
    const struct player_helper_t helper, int card_choices[], int *nchoices);
int randomcardplayer_ask_face_down_move(void);

// pyromaniac player
int pyromaniac_ask_swap_cards(const struct player_t player);
struct swap_choice_t pyromaniac_ask_swap_choice(const struct player_t player);
void pyromaniac_ask_move(const struct player_t player,
    const struct player_helper_t helper, int card_choices[], int *nchoices);
int pyromaniac_ask_face_down_move(void);

#endif
