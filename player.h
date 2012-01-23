#ifndef PLAYER_H
#define PLAYER_H 

#include "config.h"
#include "card.h"

struct player_helper_t {
    struct card_t pile[MAX_DECK_SIZE];
    int pile_size;
};

struct swap_choice_t {
    int hand_choice;
    int faceup_choice;
};

struct player_t {
    char name[MAX_NAME_LEN];
    int is_computer;
    struct card_t hand[MAX_HAND_SIZE];
    struct card_t face_up[MAX_TABLE_HAND_SIZE];
    struct card_t face_down[MAX_TABLE_HAND_SIZE];
    int hand_size;
    int face_up_size;
    int face_down_size;

    int (*ask_swap_cards)(const struct player_t);
    struct swap_choice_t (*ask_swap_choice)(const struct player_t);
    void (*ask_move)(const struct player_t, const struct player_helper_t, int[], int*);
    int (*ask_face_down_move)(void);
};

struct player_t make_player(const char *name, const char type);
void deal_to_hand(struct player_t *player, const struct card_t card);
void deal_to_face_up(struct player_t *player, const struct card_t card);
void deal_to_face_down(struct player_t *player, const struct card_t card);
void remove_from_hand(struct player_t *player, const struct card_t card);
void remove_from_face_up(struct player_t *player, const struct card_t card);
void remove_from_face_down(struct player_t *player, const struct card_t card);
void find_lowest_card_by_player(const struct player_t *players,
    const int num_players, struct card_t *cards) ;
void swap(struct player_t *player, const struct swap_choice_t choice);
int has_cards(const struct player_t player);
int has_cards_in_hand(const struct player_t player);
int ask_swap_cards(const struct player_t player);
struct swap_choice_t ask_swap_choice(const struct player_t player);
void ask_move(const struct player_t player, const struct player_helper_t helper,
    int card_choices[], int *nchoices);
int ask_face_down_move(const struct player_t player);

#endif
