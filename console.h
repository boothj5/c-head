#ifndef CONSOLE_H
#define CONSOLE_H

#include "player.h"
#include "card.h"
#include "game.h"
    
void show_welcome_msg();
void newline();
void newlines(const int num);
void clearscreen();
int request_num_players();
int request_num_cards_each();
void show_player(const struct player_t *player);
void request_player_details(char names[][MAX_NAME_LEN], char types[], const int num_players);
void show_game_summary(const struct game_t *game);
int request_swap_cards(const char *name);
int request_swap_more(const char *name);
int request_hand_swap(const int size);
int request_faceup_swap(const int size);
void request_move(const struct player_t *player, int card_choices[], int *num_choices);
void show_shithead(char *player);
void wait_user();
void show_bad_move();
void show_pickup(const char *name);
int request_face_down_move(const struct player_t *player);
void show_pickup_from_face_down(const struct card_t *card);
void show_can_move_from_face_down(const struct card_t *card);

#endif
