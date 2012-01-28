#include "player.h"
#include "player_types.h"
#include "config.h"

int human_ask_swap_cards(const struct player_t *player)
{
    // should throw error
    return FALSE;
}

struct swap_choice_t human_ask_swap_choice(const struct player_t *player)
{
    // should throw error
    struct swap_choice_t choice;
    choice.hand_choice = 1;
    choice.faceup_choice = 1;
    
    return choice;
}

void human_ask_move(const struct player_t *player, const struct player_helper_t *helper,
    int card_choices[], int *nchoices)
{
    // should throw error
}

int human_ask_face_down_move(void)
{
    // should throw error
    return 1;
}
