#include "card.h"
#include "player.h"
#include "config.h"
#include "game_rules.h"

static int choose_first_playable_from(const struct card_t cards[], const int ncards,
    const struct player_helper_t *helper)
{
    int i;
    for (i = 0; i < ncards; i++)
        if (can_lay(&cards[i], helper->pile, helper->pile_size))
            return i;

    return -1;
}

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

void choose_lowest_from_sorted(const struct card_t cards[], const int ncards, 
    const struct player_helper_t *helper, int choices[], int *nchoices)
{
    int first = choose_first_playable_from(cards, ncards, helper);
    add_similar_from_sorted(cards, ncards, &cards[first], choices, nchoices);
}

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
