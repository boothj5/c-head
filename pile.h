#ifndef PILE_H
#define PILE_H

#include "card.h"
#include "game.h"

int burn_cards_laid(const struct card_t *pile, const int pile_size);
int miss_a_go_card_laid(const struct card_t *pile, const int pile_size);
void add_to_pile(struct card_t pile[], int *pile_size, const struct card_t card);

#endif
