#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "card.h"
#include "game.h"
#include "game_rules.h"
#include "console.h"

static void perform_swap(struct game_t *game);
static void perform_last_cards_move(struct game_t *game);
static void perform_move(struct game_t *game);

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

static void perform_last_cards_move(struct game_t *game)
{
    int face_down_choice;
    struct player_t *player = &game->players[game->current_player]; 

    face_down_choice = request_face_down_move(*player);

    if (can_lay_from_face_down(*game, face_down_choice-1)) {
        show_can_move_from_face_down(player->face_down[face_down_choice-1]);
        wait_user();
        make_move_from_face_down(game, face_down_choice-1);
        clearscreen();
        show_game_summary(*game);
        move_to_next_player(game);
    } else {
        show_pickup_from_face_down(player->face_down[face_down_choice-1]);
        wait_user();
        pick_up_pile_and_face_down(game, face_down_choice-1);
        clearscreen();
        show_game_summary(*game);
        move_to_next_player(game);
    }
}

static void perform_move(struct game_t *game)
{
    int card_choices[20];
    int num_choices = 0;
    struct player_t *player = &game->players[game->current_player];

    if (can_move(*game)) {
        newline();
        request_move(*player, card_choices, &num_choices);

        if (valid_move(*game, card_choices, num_choices)) {
            make_move(game, card_choices, num_choices);
            num_choices = 0;
            clearscreen();
            show_game_summary(*game);
            move_to_next_player(game);
        } else {
            num_choices = 0;
            show_bad_move();
        }
    } else {
        show_pickup(player->name);
        wait_user();
        pick_up_pile(game);
        num_choices = 0;
        clearscreen();
        show_game_summary(*game);
        move_to_next_player(game);
    }
}

static void perform_swap(struct game_t *game)
{
    int i, do_swap, hand_choice, face_up_choice;
    struct player_t *player;

    for (i = 0; i < game->num_players; i++) {
        player = &game->players[i];
        clearscreen();
        show_player(*player);
        do_swap = request_swap_cards(player->name);

        while (do_swap) {
            clearscreen();
            show_player(*player);
            newline();
            hand_choice = request_hand_swap(player->hand_size);
            face_up_choice = request_faceup_swap(player->face_up_size);
            swap(player, hand_choice, face_up_choice);
            clearscreen();
            show_player(*player);
            newline();
            do_swap = request_swap_more(player->name);
       }
    }
}


