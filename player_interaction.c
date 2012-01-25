#include <stdio.h>
#include "player_interaction.h"
#include "game.h"
#include "player.h"
#include "console.h"
#include "game_rules.h"

void perform_swap(struct game_t *game)
{
    struct swap_choice_t choice;
    int i, do_swap, hand_choice, face_up_choice;
    struct player_t *player;

    for (i = 0; i < game->num_players; i++) {
        player = &game->players[i];

        if (player->is_computer) {
            do_swap = ask_swap_cards(*player);
            
            while (do_swap) {
                choice = ask_swap_choice(*player);
                swap(player, choice);
                do_swap = ask_swap_cards(*player);
            }
        }
        else {
            clearscreen();
            show_player(*player);
            do_swap = request_swap_cards(player->name);

            while (do_swap) {
                clearscreen();
                show_player(*player);
                newline();
                hand_choice = request_hand_swap(player->hand_size);
                face_up_choice = request_faceup_swap(player->face_up_size);
                choice.hand_choice = hand_choice;
                choice.faceup_choice = face_up_choice;
                swap(player, choice);
                clearscreen();
                show_player(*player);
                newline();
                do_swap = request_swap_more(player->name);
           }
        }
    }
}

void perform_move(struct game_t *game)
{
    int card_choices[20];
    int num_choices = 0;
    struct player_t *player = &game->players[game->current_player];

    if (can_move(*game)) {
        if (player->is_computer) {
            struct player_helper_t helper = get_player_helper(game);
            ask_move(*player, helper, card_choices, &num_choices);
            if (valid_move(*game, card_choices, num_choices)) {
                make_move(game, card_choices, num_choices); 
                num_choices = 0;
                move_to_next_player(game);
            } else {
                printf("BAD COMP MOVE");
                exit(1);
            }
        } else {
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
        }
    } else {
        if (player->is_computer) {
            pick_up_pile(game);
            num_choices = 0;
            move_to_next_player(game);
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
}

void perform_last_cards_move(struct game_t *game)
{
    int face_down_choice;
    struct player_t *player = &game->players[game->current_player];

    if (player->is_computer) {
        face_down_choice = ask_face_down_move(*player);
        
        if (can_lay_from_face_down(*game, face_down_choice-1)) {
            make_move_from_face_down(game, face_down_choice-1);
            move_to_next_player(game);
        } else {
            pick_up_pile_and_face_down(game, face_down_choice-1);
            move_to_next_player(game);
        }
    } else {
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
}

