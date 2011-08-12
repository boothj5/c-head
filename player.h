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
    Card hand[MAX_HAND_SIZE] ;
    int hand_size ;
    Card face_up[MAX_TABLE_HAND_SIZE] ;
    int face_up_size ;
    Card face_down[MAX_TABLE_HAND_SIZE] ;
    int face_down_size ;
} Player ;

Player make_player(char *name, int type) ;
void deal_to_hand(Player *p, Card c) ;
void deal_to_face_up(Player *p, Card c) ;
void deal_to_face_down(Player *p, Card c) ;

#endif
