#include "player.h"
#include "player_types.h"
#include "util.h"

int human_ask_swap_cards(struct player_t player)
{
    return FALSE;
}

struct swap_choice_t human_ask_swap_choice(struct player_t player)
{
    struct swap_choice_t choice;
    choice.hand_choice = 1;
    choice.faceup_choice = 1;
    
    return choice;
}
