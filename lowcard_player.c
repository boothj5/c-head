#include "player.h"
#include "player_types.h"
#include "util.h"

int lowcardplayer_ask_swap_cards(struct player_t player)
{
    return FALSE;
}

struct swap_choice_t lowcardplayer_ask_swap_choice(struct player_t player)
{
    struct swap_choice_t choice;
    choice.hand_choice = 0;
    choice.faceup_choice = 0;
    
    return choice;
}
