#include "card.h"
#include "player.h"
#include "config.h"
#include "game_rules.h"

// Helper functions -----------------------------------------------------------

static void shuffle(int *choices, int nchoices)
{
    int i, j, t;

    if (nchoices > 1) {
        for (i = 0; i < nchoices; i++) {
            j = rand() / (RAND_MAX / nchoices + 1);
            t = choices[j];
            choices[j] = choices[i];
            choices[i] = t;
        }
    }
}

// go through cards, return index of first playable
static int choose_first_playable_from(const struct card_t cards[], 
    const int ncards, const struct player_helper_t *helper)
{
    int i;
    for (i = 0; i < ncards; i++)
        if (can_lay(&cards[i], helper->pile, helper->pile_size))
            return i;

    return -1;
}

// add cards of same rank to choice, assume cards are sorted
static void add_similar_from_sorted(const struct card_t cards[], const int ncards,
    const struct card_t *first, int choices[], int *nchoices)
{
    int i;
    int found = FALSE;
    for (i = 0; i < ncards; i++) {
        if (ranks_equal(&cards[i], first)) {
            choices[*nchoices] = i;
            (*nchoices)++;
            found = TRUE;
        } else if (found) {
            break;
        }
    }
}

// add cards of same rank to choice, assume cards are unsorted
static void add_similar_from_unsorted(const struct card_t cards[], const int ncards,
    const struct card_t *first, int choices[], int *nchoices)
{
    int i;
    for (i = 0; i < ncards; i++) {
        if (ranks_equal(&cards[i], first)) {
            choices[*nchoices] = i;
            (*nchoices)++;
        }
    }
}

// Function callable by players -----------------------------------------------

// choose all lowest cards of same rank, assumes cards already sorted
void choose_lowest_from_sorted(const struct card_t cards[], const int ncards, 
    const struct player_helper_t *helper, int choices[], int *nchoices)
{
    int first = choose_first_playable_from(cards, ncards, helper);
    add_similar_from_sorted(cards, ncards, &cards[first], choices, nchoices);
}

// choose all lowest cards of same rank, assumes cards not sorted
void choose_lowest_from_unsorted(const struct card_t cards[], const int ncards,
    const struct player_helper_t *helper, int choices[], int *nchoices)
{
    struct card_t sorted[ncards];
    int i;
    for (i = 0; i<ncards; i++)
        sorted[i] = cards[i];
    sort_cards(sorted, ncards);

    int first = choose_first_playable_from(sorted, ncards, helper);
    add_similar_from_unsorted(cards, ncards, &sorted[first], choices, nchoices);
}

// choose randomly cards of same rank, assumes cards are sorted
void choose_random_from_sorted(const struct card_t cards[], const int ncards,
    const struct player_helper_t *helper, int choices[], int *nchoices)
{
    int i;

    int possible_choices[ncards];
    for (i = 0; i < ncards; i++) {
        possible_choices[i] = i;
    }

    shuffle(possible_choices, ncards);

    int first = 0;
    for (i = 0; i < ncards; i++) {
        if (can_lay(&cards[possible_choices[i]], helper->pile, helper->pile_size)) {
            first = possible_choices[i];
            break;
        }
    }

    add_similar_from_sorted(cards, ncards, &cards[first], choices, nchoices);
}

void choose_random_from_unsorted(const struct card_t cards[], const int ncards,
    const struct player_helper_t *helper, int choices[], int *nchoices)
{
    int first = choose_first_playable_from(cards, ncards, helper);
    add_similar_from_unsorted(cards, ncards, &cards[first], choices, nchoices);
}


// chooses burn cards, or nothing if none, assumes cards already sorted
void choose_burn_from_sorted(const struct card_t cards[], const int ncards,
    const struct player_helper_t *helper, int choices[], int *nchoices)
{
    int i;
    for (i = ncards-1; i>=0 ; i--) {
        if (cards[i].rank == BURN) {
            choices[*nchoices] = i;
            (*nchoices)++;
        } else if (!special_card(&cards[i])) {
            break;
        }
    }
}

// chooses burn cards, or nothing if none, assumes cards not sorted
void choose_burn_from_unsorted(const struct card_t cards[], const int ncards,
    const struct player_helper_t *helper, int choices[], int *nchoices)
{
    int i;
    for (i = 0; i < ncards; i++) {
        if (cards[i].rank == BURN) {
            choices[*nchoices] = i;
            (*nchoices)++;
        }
    }
}    
 
