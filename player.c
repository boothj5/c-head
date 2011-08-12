#include <string.h>
#include "player.h"

Player make_player(char *name, int type) 
{
    Player result ;
    strcpy(result.name, name) ;
    result.type = type ;
    result.hand_size = 0 ;
    result.face_up_size = 0 ;
    result.face_down_size = 0 ;
    return result ;
}

void deal_to_hand(Player *p, Card c)
{
    p->hand[p->hand_size++] = c ;
}

void deal_to_face_up(Player *p, Card c)
{
    p->face_up[p->face_up_size++] = c ;
}

void deal_to_face_down(Player *p, Card c)
{
    p->face_down[p->face_down_size++] = c ;
}
