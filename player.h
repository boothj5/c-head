#ifndef PLAYER_H
#define PLAYER_H 

#include "card.h"

#define MAX_HAND_SIZE 100
#define MAX_TABLE_HAND_SIZE 10
#define MAX_NAME_LEN 10

enum player_types { HUMAN, COMPUTER } ;

typedef struct player_t *Player ;

Player make_player(char *name, int type) ;
void deal_to_hand(Player p, Card c) ;
void deal_to_face_up(Player p, Card c) ;
void deal_to_face_down(Player p, Card c) ;
char *player_name(Player p) ;
int hand_size(Player p) ;
int face_up_size(Player p) ;
int face_down_size(Player p) ;
Card *hand(Player p) ;
Card *face_up(Player p) ;
Card *face_down(Player p) ;

#endif
