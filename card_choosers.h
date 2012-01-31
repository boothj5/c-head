#ifndef CARD_CHOOSERS_H
#define CARD_CHOOSERS_H

#include "card.h"
#include "player.h"

void choose_lowest_from_sorted(const struct card_t cards[], const int ncards, 
    const struct player_helper_t *helper, int choices[], int *nchoices);

void choose_lowest_from_unsorted(const struct card_t cards[], const int ncards, 
    const struct player_helper_t *helper, int choices[], int *nchoices);

void choose_random_from_sorted(const struct card_t cards[], const int ncards, 
    const struct player_helper_t *helper, int choices[], int *nchoices);

void choose_random_from_unsorted(const struct card_t cards[], const int ncards, 
    const struct player_helper_t *helper, int choices[], int *nchoices);

void choose_burn_from_sorted(const struct card_t cards[], const int ncards,
    const struct player_helper_t *helper, int choices[], int *nchoices);

void choose_burn_from_unsorted(const struct card_t cards[], const int ncards,
    const struct player_helper_t *helper, int choices[], int *nchoices);

#endif
