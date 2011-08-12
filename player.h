#ifndef PLAYER_H
#define PLAYER_H 

#include "card.h"

#define MAX_HAND_SIZE 100
#define MAX_TABLE_HAND_SIZE 10
#define MAX_NAME_LEN 10

enum player_types { HUMAN, COMPUTER } ;

typedef struct {
    char name[MAX_NAME_LEN] ;
    int type ;
    card hand[MAX_HAND_SIZE] ;
    int hand_size ;
    card face_up[MAX_TABLE_HAND_SIZE] ;
    int face_up_size ;
    card face_down[MAX_TABLE_HAND_SIZE] ;
    int face_down_size ;

} player ;

player make_player(char *, int) ;
void deal_to_hand(player *, card) ;
void deal_to_face_up(player *, card) ;
void deal_to_face_down(player *, card) ;

#endif
