#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "game.h"
#include "console.h"
#include "player_interaction.h"

int main(void)
{
    struct game_t game;
    int nplayers, ncards;
    char names[MAX_NUM_PLAYERS][MAX_NAME_LEN];
    char types[MAX_NUM_PLAYERS];
    struct player_t shithead;
    
    clearscreen();
    show_welcome_msg();
    nplayers = request_num_players();
    ncards = request_num_cards_each();
    request_player_details(names, types, nplayers);
    game = make_game(nplayers, names, types, ncards);
    init_game(&game);
    perform_swap(&game);
    first_move(&game);
    clearscreen();
    show_game_summary(game);

    while (continue_play(game))
        if (player_on_last_cards(&game))
            perform_last_cards_move(&game);
        else
            perform_move(&game);

    shithead = get_shithead(game);
    show_shithead(shithead);

    return 0;
}
