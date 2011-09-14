#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "card.h"
#include "game.h"
#include "console.h"

static void perform_swap(struct game_t *game) ;

int main(void)
{
    struct game_t game ;
    int nplayers, ncards ;
    char names[MAX_NUM_PLAYERS][MAX_NAME_LEN] ;
    int choice ;
    struct player_t shithead ;
    
    clearscreen() ;
    show_welcome_msg() ;
    nplayers = request_num_players() ;
    ncards = request_num_cards_each() ;
    request_player_names(names, nplayers) ;
    game = make_game(nplayers, names, ncards) ;
    perform_swap(&game) ;
    first_move(&game) ;
    clearscreen() ;
    show_game_summary(game) ;

    while (continue_play(game)) {
        newline() ;
        choice = request_move(game.players[game.current_player]) ;
        show_cards(&game.players[game.current_player].hand[choice-1], 1) ;
        make_move(&game, choice-1) ;    
        clearscreen() ;
        show_game_summary(game) ;
    }

    shithead = get_shithead(game) ;
    show_shithead(shithead) ;

    return 0 ;
}

static void perform_swap(struct game_t *game)
{
    int i, do_swap, hand_choice, face_up_choice ;
    struct player_t *player ;

    for (i = 0 ; i < game->num_players ; i++) {
        player = &game->players[i] ;
        clearscreen() ;
        show_player(*player) ;
        do_swap = request_swap_cards(player->name) ;
        while (do_swap) {
            clearscreen() ;
            show_player(*player) ;
            newline() ;
            hand_choice = request_hand_swap(player->hand_size) ;
            face_up_choice = request_faceup_swap(player->face_up_size) ;
            swap(player, hand_choice, face_up_choice) ;
            clearscreen() ;
            show_player(*player) ;
            newline() ;
            do_swap = request_swap_more(player->name) ;
       }
    }
}


