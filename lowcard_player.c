#include <stdio.h>
#include "player.h"
#include "player_types.h"
#include "util.h"
#include "game_rules.h"
#include "card.h"

int lowcardplayer_ask_swap_cards(const struct player_t player)
{
    return FALSE;
}

struct swap_choice_t lowcardplayer_ask_swap_choice(const struct player_t player)
{
    // should throw error
    struct swap_choice_t choice;
    choice.hand_choice = 1;
    choice.faceup_choice = 1;
    
    return choice;
}

void lowcardplayer_ask_move(const struct player_t player, 
    const struct player_helper_t helper, int card_choices[], int *nchoices)
{
    *nchoices = 0;
    int first = 0;
    if (has_cards_in_hand(player)) {
        // play from hand
        // assume my hand is sorted
        // find the first card I can lay and save its index
        int i;
        for (i = 0; i < player.hand_size; i++) {
            if (can_lay(player.hand[i], helper.pile, helper.pile_size)) {
                first = i;
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

        // copy and sort my faceUp
        struct card_t sorted[player.face_up_size];
        int i;
        for (i = 0; i<player.face_up_size; i++)
            sorted[i] = player.face_up[i];
        sort_cards(sorted, player.face_up_size);

        // find the first card I can lay and save its index
        for (i = 0; i < player.face_up_size; i++) {
            if (can_lay(sorted[i], helper.pile, helper.pile_size)) {
                first = i;
                break;
            }
        }

        // add all cards of this rank to my choice
        for (i = 0; i < player.face_up_size; i++) {
            if (ranks_equal(player.face_up[i], sorted[first])) {
                card_choices[*nchoices] = i;
                (*nchoices)++;
            }
        }
    }
}

int lowcardplayer_ask_face_down_move(void)
{
    return 1;
}

