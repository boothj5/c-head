#include <stdio.h>
#include <time.h>
#include "player.h"
#include "player_types.h"
#include "config.h"
#include "util.h"
#include "card_choosers.h"

int randomcardplayer_ask_swap_cards(const struct player_t *player)
{
    return FALSE;
}

struct swap_choice_t randomcardplayer_ask_swap_choice(const struct player_t *player)
{
    // should throw error
    struct swap_choice_t choice;
    choice.hand_choice = 1;
    choice.faceup_choice = 1;
    
    return choice;
}

void randomcardplayer_ask_move(const struct player_t *player, 
    const struct player_helper_t *helper, int card_choices[], int *nchoices)
{
    *nchoices = 0;
    
    if (has_cards_in_hand(player)) {
        choose_random_from_sorted(player->hand, player->hand_size, helper,
            card_choices, nchoices);
    } else {
        choose_random_from_unsorted(player->face_up, player->face_up_size, helper,
            card_choices, nchoices);
    }
}

int randomcardplayer_ask_face_down_move(void)
{
    return 1;
}

