#ifndef CARD_H
#define CARD_H

#include <stdlib.h>

enum cardrank { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
                JACK, QUEEN, KING, ACE };

enum cardsuit { HEARTS, SPADES, DIAMONDS, CLUBS };

struct card_t {
    enum cardrank rank;
    enum cardsuit suit;
};

struct card_t make_card(const enum cardrank rank, const enum cardsuit suit);
struct card_t find_lowest_card(const struct card_t *cards, const int num_cards);
int special_card(const struct card_t card);
int card_cmp(const void *card1, const void *card2);
int cards_equal(const struct card_t card1, const struct card_t card2);
int ranks_equal(const struct card_t card1, const struct card_t card2);
int all_ranks_equal(const struct card_t *cards, const int num_cards);
char* show_rank(const struct card_t card);
char* show_suit(const struct card_t card);
void add_card_to_cards(struct card_t cards[], int *num_cards, 
    const struct card_t card);
void remove_card_from_cards(struct card_t cards[], int *num_cards, 
    const struct card_t card);
void sort_cards(struct card_t *cards, const int num_cards);

#endif
