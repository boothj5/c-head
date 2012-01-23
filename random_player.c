#include <stdio.h>
#include <time.h>
#include "player.h"
#include "player_types.h"
#include "config.h"
#include "game_rules.h"
#include "card.h"

static void shuffle(int *choices, int nchoices)
{
    int i, j, t;

    if (nchoices > 1) {
        srand((unsigned)time(NULL)) ;
        for (i = 0; i < nchoices - 1; i++) {
            j = i + rand() / (RAND_MAX / (nchoices - i) + 1);
            t = choices[j];
            choices[j] = choices[i];
            choices[i] = t;
        }
    }
}

int randomcardplayer_ask_swap_cards(const struct player_t player)
{
    return FALSE;
}

struct swap_choice_t randomcardplayer_ask_swap_choice(const struct player_t player)
{
    // should throw error
    struct swap_choice_t choice;
    choice.hand_choice = 1;
    choice.faceup_choice = 1;
    
    return choice;
}

void randomcardplayer_ask_move(const struct player_t player, 
    const struct player_helper_t helper, int card_choices[], int *nchoices)
{
    *nchoices = 0;
    int first = 0;
    if (has_cards_in_hand(player)) {
        // play from hand
        // shuffle possible indexes
        int possible_choices[player.hand_size];
        int i;
        for (i = 0; i < player.hand_size; i++) {
            possible_choices[i] = i;
        }
        shuffle(possible_choices, player.hand_size);

        // find the first card I can lay and save its index
        for (i = 0; i < player.hand_size; i++) {
            if (can_lay(player.hand[possible_choices[i]], helper.pile, helper.pile_size)) {
                first = possible_choices[i];
                break;
            }
        }

        // add all cards of same rank from my hand to my choice
        int found = FALSE;
        for (i = 0; i < player.hand_size; i++) {
            if (ranks_equal(player.hand[i], player.hand[first])) {
                card_choices[*nchoices] = i;
                (*nchoices)++;
                found = TRUE;
            } else if (found) {
                break;
            }
        }
    } else {
        // play from faceUp

        // find the first card I can lay and save its index
        int i;
        for (i = 0; i < player.face_up_size; i++) {
            if (can_lay(player.face_up[i], helper.pile, helper.pile_size)) {
                first = i;
                break;
            }
        }

        // add all cards of this rank to my choice
        for (i = 0; i < player.face_up_size; i++) {
            if (ranks_equal(player.face_up[i], player.face_up[first])) {
                card_choices[*nchoices] = i;
                (*nchoices)++;
            }
        }
    }
}

int randomcardplayer_ask_face_down_move(void)
{
    return 1;
}

