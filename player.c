#include <string.h>
#include "player.h"

player make_player(char *name, int type) 
{
    player result ;
    strcpy(result.name, name) ;
    result.type = type ;
    result.hand_size = 0 ;
    result.face_up_size = 0 ;
    result.face_down_size = 0 ;
    return result ;
}

void deal_to_hand(player *p, card c)
{
    p->hand[p->hand_size++] = c ;
}

void deal_to_face_up(player *p, card c)
{
    p->face_up[p->face_up_size++] = c ;
}

void deal_to_face_down(player *p, card c)
{
    p->face_down[p->face_down_size++] = c ;
}
