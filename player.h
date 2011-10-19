#ifndef PLAYER_H
#define PLAYER_H 

#include "card.h"

#define MAX_HAND_SIZE 100
#define MAX_TABLE_HAND_SIZE 10
#define MAX_NAME_LEN 10

enum player_types { HUMAN, COMPUTER } ;

struct player_t {
    char name[MAX_NAME_LEN] ;
    int type ;
    struct card_t hand[MAX_HAND_SIZE] ;
    struct card_t face_up[MAX_TABLE_HAND_SIZE] ;
    struct card_t face_down[MAX_TABLE_HAND_SIZE] ;
    int hand_size ;
    int face_up_size ;
    int face_down_size ;
} ;

struct player_t make_player(char *name, int type) ;
void deal_to_hand(struct player_t *player, struct card_t card) ;
void deal_to_face_up(struct player_t *player, struct card_t card) ;
void deal_to_face_down(struct player_t *player, struct card_t card) ;
void remove_from_hand(struct player_t *player, struct card_t card) ;
void remove_from_face_up(struct player_t *player, struct card_t card) ;
void remove_from_face_down(struct player_t *player, struct card_t card) ;
void find_lowest_card_by_player(struct player_t *players, int num_players, struct card_t *cards) ;
void swap(struct player_t *player, int hand_index, int faceup_index) ;
int has_cards(struct player_t player) ;

#endif
